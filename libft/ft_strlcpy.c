/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rralambo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:55:28 by rralambo          #+#    #+#             */
/*   Updated: 2022/11/15 14:30:56 by rralambo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len_s;

	len_s = ft_strlen(src);
	if (size == 0)
		return (len_s);
	if (len_s < size)
		ft_memcpy(dst, src, len_s + 1);
	else
	{
		ft_memcpy(dst, src, size - 1);
		dst[size - 1] = '\0';
	}
	return (len_s);
}

/*
int	main()
{
	char a[] = "Ceci est un test";
	char b[10]; memset(b, 'A', 10);

	//printf("%ld : %ld\n", strlcpy(b,a,50),ft_strlcpy(b,a,50));
	printf("%ld\n", ft_strlcpy(b,a,1));
	printf("%s\n", b);
}*/
