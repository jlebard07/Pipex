/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:26:35 by jlebard           #+#    #+#             */
/*   Updated: 2024/05/28 15:26:35 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	count_quote(char *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] == 39)
			j++;
		i++;
	}
	return (j);
}

void	exec(char *cmd, char **env)
{
	char	**cmd_exec;
	char	*path;

	if (count_quote(cmd) == 0)
		cmd_exec = ft_split(cmd, ' ');
	else
		cmd_exec = split_if_quote(cmd);
	if (cmd_exec == NULL)
	{
		ft_putstr_fd("Mauvais format de commande\n", 2);
		exit(1);
	}
	path = get_path(cmd_exec[0], env);
	if (path == NULL)
	{
		free_tab(cmd_exec);
		display_error();
	}
	if (execve(path, cmd_exec, NULL) == -1)
	{
		free(path);
		free_tab(cmd_exec);
		display_error();
	}
}

void	child_process(int *p_fd, char **argv, char **env)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Echec lors de l'ouverture d'un fichier\n", 2);
		close(p_fd[1]);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[1]);
	close(fd);
	exec(argv[2], env);
}

void	parent_process(int *p_fd, char **argv, char **env)
{
	int	fd;

	fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0755);
	if (fd == -1)
	{
		ft_putstr_fd("Echec lors de l'ouverture d'un fichier\n", 2);
		close(p_fd[0]);
		exit(1);
	}
	dup2(p_fd[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(p_fd[0]);
	close(fd);
	exec(argv[3], env);
}

int	main(int argc, char **argv, char **env)
{
	int		p_fd[2];
	pid_t	pid;

	if (argc != 5)
		return (-1);
	if (pipe(p_fd) == -1)
		display_error();
	pid = fork();
	if (pid < 0)
		display_error();
	if (pid == 0)
	{
		close (p_fd[0]);
		child_process(p_fd, argv, env);
	}
	else if (pid != 0)
	{
		close(p_fd[1]);
		wait(NULL);
		parent_process(p_fd, argv, env);
	}		
}
