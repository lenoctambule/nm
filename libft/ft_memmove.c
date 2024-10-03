/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rralambo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:38:46 by rralambo          #+#    #+#             */
/*   Updated: 2022/11/23 16:20:00 by rralambo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*copy_r(char *d, char *s, size_t n)
{
	int	i;

	i = n - 1;
	while (i >= 0)
	{
		d[i] = s[i];
		i--;
	}
	return (d);
}

static void	*copy_l(char *d, char *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	char		*s;

	s = (char *)src;
	d = (char *)dest;
	if (d == s || dest == NULL || src == NULL)
		return (dest);
	if (d > s && s + n > d)
	{
		return (copy_r(d, s, n));
	}
	if (d < s && d + n > s)
	{
		return (copy_l(d, s, n));
	}
	return (ft_memcpy(d, s, n));
}

/*
int	main()
{
	char	a[] = "0123456789abcX";
	char *src = a;
	char *dest = a+1;

	ft_memmove(dest,src,5);
	//memmove(dest,src,5);
	printf("%s\n", a);
}*/
