/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rralambo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:03:52 by rralambo          #+#    #+#             */
/*   Updated: 2022/11/22 11:40:07 by rralambo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*t;

	i = 0;
	if (s == NULL)
		return (NULL);
	t = (unsigned char *)s;
	while (i < n)
	{
		if (t[i] == (unsigned char)c)
			return (t + i);
		i++;
	}	
	return (NULL);
}

/*
int	main()
{
	int	t = 0xdeadbeef;

	printf("%c", *(char *)ft_memchr(&t, '\xef', 4));
}*/
