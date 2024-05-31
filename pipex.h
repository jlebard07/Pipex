/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:30:03 by jlebard           #+#    #+#             */
/*   Updated: 2024/05/28 15:30:03 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

int		main(int argc, char **argv, char **env);
void	parent_process(int *p_fd, char **argv, char **env);
void	child_process(int *p_fd, char **argv, char **env);
void	free_tab(char **tab);
void	display_error(void);
char	*get_path(char	*cmd, char **env);
char	**split_if_quote(char *str);
int		count_quote(char *cmd);

#endif