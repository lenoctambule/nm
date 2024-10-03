/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rralambo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:48:30 by rralambo          #+#    #+#             */
/*   Updated: 2022/11/23 18:25:06 by rralambo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*t_dst;
	char		*t_src;

	if (dest == NULL || src == NULL)
		return (dest);
	t_src = (char *)src;
	t_dst = (char *)dest;
	i = 0;
	while (i < n)
	{
		t_dst[i] = t_src[i];
		i++;
	}
	return (dest);
}

/*
int	main()
{
	char dst[] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAJHH";
	char src[] = "ceci est un test";
	
	printf("%s\n", ft_memcpy(dst, src, 8));
	return (0);
}*/
