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

void	display_error(void)
{
	int	save_errno;

	save_errno = errno;
	ft_putstr_fd("Type d'erreur :", 2);
	ft_putstr_fd(strerror(save_errno), 2);
	write(2, "\n", 1);
	exit(1);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i])
		i++;
	while (i > 0)
	{
		i--;
		free (tab[i]);
	}
	free(tab);
}

static char	*get_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
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
	{
		free(exec_repo);
		free(cmd_searched);
		return (NULL);
	}
	i = 0;
	while (exec_repo[i])
	{
		temp_exec = ft_strjoin(exec_repo[i], "/");
		exec = ft_strjoin(temp_exec, cmd_searched[0]);
		free(temp_exec);
		if (access(exec, F_OK | X_OK) == 0)
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
