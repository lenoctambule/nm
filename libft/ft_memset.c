/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rralambo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:25:25 by rralambo          #+#    #+#             */
/*   Updated: 2022/11/22 11:41:05 by rralambo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*temp;

	i = 0;
	if (s == NULL)
		return (NULL);
	temp = (char *)s;
	while (i < n)
		temp[i++] = c;
	return (temp);
}

/*
int main()
{
	//char t[] = "ceci est un test";
	int t;

	t = 0;
	printf("%d\n", t);
	ft_memset(&t, 'a', 1);
	printf("%d\n", t);
}
*/
