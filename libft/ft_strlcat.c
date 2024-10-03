/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rralambo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:48:38 by rralambo          #+#    #+#             */
/*   Updated: 2022/11/16 13:37:59 by rralambo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	ld;
	size_t	ls;

	i = 0;
	ls = ft_strlen(src);
	if (dst == NULL && size == 0)
		return (ls);
	while (dst[i] && i < size)
		i++;
	ld = i;
	if (size == 0)
		return (ld + ls);
	j = 0;
	while (src[j] && i < size - 1)
	{
		dst[i] = src[j];
		j++;
		i++;
	}
	if (i < size)
		dst[i] = 0;
	return (ld + ls);
}

/*
#define SIZE 18
#include <assert.h>

int	main()
{
	char	dest[50];
	char	src[] = "AAAAAAAAA";
	memset(dest,0,30);
	memset(dest, 'C', 5);
	printf("%d :%s\n", ft_strlcat(NULL,src,0), dest);
}*/
