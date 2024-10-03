/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rralambo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:12:17 by rralambo          #+#    #+#             */
/*   Updated: 2022/11/15 15:21:35 by rralambo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	ft_atoi(const char *nptr)
{
	int	res;
	int	sign;

	sign = 1;
	res = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (ft_isdigit(*(nptr)))
	{
		res *= 10;
		res += sign * (*nptr % '0');
		nptr++;
	}	
	return (res);
}

/*
int	main(int ac, char **av)
{
	printf("%d\n", ft_atoi("   46\b9 \n5d6"));
}*/
