/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rralambo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:02:01 by rralambo          #+#    #+#             */
/*   Updated: 2022/11/14 13:30:14 by rralambo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_fd_recu(int n, int fd)
{
	char	digit;

	if (n < 0)
	{
		write(fd, "-", 1);
		n = n * (-1);
	}
	if (n > 0)
	{
		ft_putnbr_fd_recu(n / 10, fd);
		digit = '0' + n % 10;
		write(fd, &digit, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == 0)
		write(fd, "0", 1);
	else if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
		ft_putnbr_fd_recu(n, fd);
}

/*
int	main(int ac, char **av)
{
	ft_putnbr_fd(atoi(av[1]), 1);
}*/
