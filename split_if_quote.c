/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_if_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 09:14:17 by jlebard           #+#    #+#             */
/*   Updated: 2024/05/31 14:54:37 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	change_space(char *str, int n)
{
	int	i;

	i = 0;
	while (str[i] && i < n)
	{
		if (str[i] == ' ')
			str[i] = '\n';
		i++;
	}
}

static size_t	tab_size(char **tab)
{
	size_t	n;

	n = 0;
	while (tab[n])
		n++;
	return (n);
}

static char	*write_space(char *temp, char *dest)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (temp[i])
	{
		if (temp[i] != 39)
		{
			if (temp[i] == '\n')
				dest[j] = ' ';
			else
			{
				dest[j] = temp[i];
			}
			j++;
		}
		i++;
	}
	dest[j] = '\0';
	return (dest);
}

static char	**return_space(char **temp)
{
	char	**dest;
	int		i;

	dest = (char **)malloc(sizeof(char *) * (tab_size(temp) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (temp[i])
	{
		dest[i] = malloc(sizeof(char) * \
		((int)ft_strlen(temp[i]) - count_quote(temp[i]) + 1));
		if (!dest[i])
			return (NULL);
		dest[i] = write_space(temp[i], dest[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

char	**split_if_quote(char *str)
{
	int		i;
	int		j;
	char	**temp;
	char	**dest;

	if (count_quote(str) % 2 == 1)
		return (NULL);
	i = 0;
	while (str[i++])
	{
		j = 1;
		if (str[i] == 39)
		{
			while (str[i + j] && str[i + j] != 39)
				j++;
			if (str[i + j] == 39)
				change_space(str + i, j);
			i += j;
		}
	}
	temp = ft_split(str, ' ');
	dest = return_space(temp);
	free_tab(temp);
	return (dest);
}
