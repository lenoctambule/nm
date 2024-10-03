/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rralambo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:50:31 by rralambo          #+#    #+#             */
/*   Updated: 2022/11/14 17:13:15 by rralambo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*r;

	r = (char *)s + ft_strlen(s);
	while (r != s && *r != (char)c)
		r--;
	if (r == s && *r != (char)c)
		return (NULL);
	return (r);
}

/*
int	main()
{
	printf("%s", ft_strrchr("Ceci est un test", 'c'));
	return 0;
}*/
