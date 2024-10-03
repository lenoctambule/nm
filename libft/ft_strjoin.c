/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rralambo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:12:33 by rralambo          #+#    #+#             */
/*   Updated: 2022/11/16 11:48:26 by rralambo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		len_s1;
	char	*res;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	i = 0;
	len_s1 = ft_strlen(s1);
	while (s2[i])
	{
		res[len_s1 + i] = s2[i];
		i++;
	}
	res[ft_strlen(s1) + i] = 0;
	return (res);
}

/*
int main(int argc, char **argv)
{
	char t1[] = "";
	char t2[] = "";
	printf("%s\n", ft_strjoin(t1,t2));
}*/
