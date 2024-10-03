/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rralambo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:34:06 by rralambo          #+#    #+#             */
/*   Updated: 2022/11/23 15:45:22 by rralambo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;
	size_t	total;

	total = nmemb * size;
	if (total != 0 && nmemb != total / size)
		return (NULL);
	res = malloc(total);
	if (res == NULL)
		return (NULL);
	ft_memset(res, 0, total);
	return (res);
}

/*
int	main()
{
	int	*t = (int *) calloc(10, sizeof(int));

	for (int i = 0; i < 10; i++)
	{
		t[i] = i;
		printf("%d  ",i);
	}
	return (0);
}*/
