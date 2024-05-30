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
	if (cmd_exec == NULL)
		display_error();
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
	write(2, "test", 4);
}

void	child_process(int *p_fd, char **argv, char **env)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		display_error();
	dup2(fd, STDIN_FILENO);
	dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[1]);
	close(fd);
	exec(argv[2], env);
}

void	parent_process(int *p_fd, char **argv, char **env)
{
	int	fd;

	fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
		display_error();
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
