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

int			main(int argc, char **argv, char **env);
char		*parent_process(int *p_fd, char **argv, char **env);
char		*child_process(int *p_fd, char **argv, char **env);
void		free_tab(char **tab);
int			count_split(char **argv);
void		display_error(void);

#endif