/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rralambo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:27:39 by rralambo          #+#    #+#             */
/*   Updated: 2022/11/16 14:01:33 by rralambo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	len_l;

	if (little[0] == '\0')
		return ((char *)big);
	if (big == NULL && len == 0)
		return (NULL);
	i = 0;
	len_l = ft_strlen(little);
	while (big[i] && i + len_l <= len)
	{
		j = 0;
		while (little[j] == big[i + j])
		{
			if (little[j + 1] == '\0')
				return ((char *)big + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

/*
int main(int ac, char **av)
{
	char a[30] = "aaabcabcd";
	char b[10] = "aabc";
	printf("%s\n", ft_strnstr("lorem ipsum dolor sit amet", "", 30));
	return (0);
}*/
