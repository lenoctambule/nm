/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rralambo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:33:57 by rralambo          #+#    #+#             */
/*   Updated: 2022/11/14 14:46:59 by rralambo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t		i;
	char		*temp;

	i = 0;
	temp = (char *)s;
	while (i < n)
		temp[i++] = 0;
}

/*
int	main()
{
	int test = 165131321;
	bzero(&test, 2);
	printf("%d\n", test);
	
}*/
