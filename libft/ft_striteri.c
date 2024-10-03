/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rralambo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:40:54 by rralambo          #+#    #+#             */
/*   Updated: 2022/11/23 12:50:07 by rralambo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	if (s == NULL || f == NULL)
		return ;
	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}

/*
char	test(unsigned int i, char *s)
{
	s[i] = s[i] + 3;
}

int	main()
{
	char t[] = "Ceci est un test";
	char *res;

	ft_striteri(t, &test);
	printf("%s\n", t);
	return (0);
}*/
