/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rralambo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:34:17 by rralambo          #+#    #+#             */
/*   Updated: 2022/11/10 14:40:42 by rralambo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	res;

	res = 0;
	while (s[res])
		res++;
	return (res);
}

/*
int main()
{
	char test[] = "ceci est un test";
	
	printf("%d\n", ft_strlen(test));
	return 0;
}
*/
