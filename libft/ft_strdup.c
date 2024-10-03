/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rralambo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:39:06 by rralambo          #+#    #+#             */
/*   Updated: 2022/11/23 17:36:59 by rralambo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*res;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s) + 1;
	res = (char *)malloc(sizeof(char) * len);
	if (res == NULL)
		return (res);
	ft_memcpy(res, s, len);
	return (res);
}

/*
int	main()
{
	char src[] = "ojala ca marche";
	char *dst = ft_strdup(src);
	printf("%p:%s\n%p:%s", src,src,dst,dst);
}*/
