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

int	main(int argc, char **argv)
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
		exit (-1);
	if (pid == 0)
	{
		
	}
}
