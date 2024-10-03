/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rralambo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:54:22 by rralambo          #+#    #+#             */
/*   Updated: 2022/11/22 11:40:49 by rralambo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*t1;
	unsigned char	*t2;

	i = 0;
	t1 = (unsigned char *)s1;
	t2 = (unsigned char *)s2;
	if (n == 0 || s1 == NULL || s2 == NULL)
		return (0);
	while (i < n)
	{
		if (t1[i] != t2[i])
			return (t1[i] - t2[i]);
		i++;
	}
	i--;
	return (t1[i] - t2[i]);
}
