/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:12:17 by jlebard           #+#    #+#             */
/*   Updated: 2023/11/22 15:56:38 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*temp1;
	unsigned char	*temp2;

	temp1 = (unsigned char *)s1;
	temp2 = (unsigned char *)s2;
	while (n > 0)
	{
		if (*temp1 != *temp2)
			return (*temp1 - *temp2);
		temp1++;
		temp2++;
		n--;
	}
	return (0);
}

// int main()
// {
// 	char *s1 = "wuhdhwu";
// 	char *s2 = "wuhdhw0";
// 	size_t n = 100;
// 	printf("%d\n", ft_memcmp(s1, s2, n));;
//	printf("vrai memcmp : %d\n", memcmp(s1, s2, n));
//	return 0;
// }
