/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rralambo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:34:55 by rralambo          #+#    #+#             */
/*   Updated: 2022/11/23 16:24:12 by rralambo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (*s && *s != (char)c)
		s++;
	if ((char)c && !*s)
		return (NULL);
	return ((char *)s);
}

/*
int	main()
{
	char t[] = "Ceci est un test";

	printf("%s",ft_strchr(t, 'z'));
	return (0);
}*/
