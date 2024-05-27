/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 19:15:43 by jlebard            #+#    #+#             */
/*   Updated: 2024/05/26 19:15:43 by jlebard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*child_process(int *p_fd, char **argv)
{
	int	fd;

	fd = open(p_fd[0], O_RDONLY)	
	dup2(fd, STDIN_FILENO);
	close(p_fd[0]);
	close(p_fd[1]);
}

char	*parent_process(int *p_fd, char **argv)
{
	int	fd;
	
	fd = open(p_fd[1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(fd, STDOUT_FILENO);
	close(p_fd);
	close(p_fd[0]);

}

int	main(int argc, char **argv, char **env)
{
	int		p_fd[2];
	pid_t	pid;
	
	if (argc == 2)
	{
		argv = ft_split(argv + 1, ' ');
		if (count_split(argv) != 4);
		{
			free_argv(argv);
			exit(1);
		}
	}
	else if (argc != 5)
		exit(1);
	if (pipe(p_fd) == -1)
		exit(-1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (pid == 0)
		child_process(p_fd, argv);
	else if (pid != 0)
		parent_process(p_fd, argv);
}
