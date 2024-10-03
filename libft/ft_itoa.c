/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rralambo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:12:51 by rralambo          #+#    #+#             */
/*   Updated: 2022/11/15 15:10:44 by rralambo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ilen(int n)
{
	int	res;

	res = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		res = 1;
	while (n != 0)
	{
		res++;
		n /= 10;
	}
	return (res);
}

static int	ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*res;

	len = ft_ilen(n);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	if (n == 0)
	{
		res[0] = '0';
		res[1] = '\0';
		return (res);
	}
	if (n < 0)
		res[0] = '-';
	res[len] = '\0';
	len -= 1;
	while (n != 0)
	{
		res[len] = '0' + ft_abs(n % 10);
		n /= 10;
		len--;
	}
	return (res);
}

/*
int	main(int ac, char **av)
{
	printf("%s\n", ft_itoa(9));
	return (0);
}*/
