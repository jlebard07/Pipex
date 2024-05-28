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

void	exec(char *cmd, char **env)
{
	char	**cmd_exec;
	char	*path;

	cmd_exec = ft_split(cmd, ' ');
	path = getpath(cmd_exec[0]);
	if (path == NULL)
		display_error();
	if (execve(path, cmd_exec, NULL) == -1)
	{
		free(path);
		free_tab(cmd_exec);
		display_error();
	}
}

char	*child_process(int *p_fd, char **argv, char **env)
{
	int	fd;

	fd = open(p_fd[0], O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(p_fd[0]);
	close(p_fd[1]);
}

char	*parent_process(int *p_fd, char **argv, char **env)
{
	int	fd;

	fd = open(p_fd[1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(fd, STDOUT_FILENO);
	close(p_fd[1]);
	close(p_fd[0]);
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
	if (pid == -1)
		display_error();
	if (pid == 0)
		child_process(p_fd, argv, env);
	else if (pid != 0)
		parent_process(p_fd, argv, env);
}
