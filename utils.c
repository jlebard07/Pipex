/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:27:52 by jlebard           #+#    #+#             */
/*   Updated: 2024/05/28 15:27:52 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	count_split(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

void	display_error(void)
{
	ft_putstr_fd("Error :", 2);
	ft_putstr_fd(strerror(errno), 2);
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	*get_env(char **env)
{
	char	*path;
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			if (ft_strncmp(env[i] + j, "PATH=", 5) == 0)
				return (env[i] + j + 1);
			j++;
		}
		i++;
	}
	return (NULL);
}

char	*get_path(char	*cmd, char **env)
{
	int		i;
	char	*temp_exec;
	char	**exec_repo;
	char	*exec;
	char	**cmd_searched;

	exec_repo = ft_split(get_env(env), ':');
	cmd_searched = ft_split(cmd, ' ');
	if (!cmd_searched || !exec_repo)
		return (NULL);
	i = 0;
	while (exec_repo[i])
	{
		temp_exec = ft_strjoin(exec_repo[i], "/");
		exec = ft_strjoin(temp_exec, cmd_searched[0]);
		free(temp_exec);
		if (acess(exec, F_OK | X_OK) == 0)
		{
			free_tab(exec_repo);
			free_tab(cmd_searched);
			return (exec);
		}
		free(exec);
		i++;
	}
	free_tab(exec_repo);
	free_tab(cmd_searched);
	return (NULL);
}
