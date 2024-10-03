/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rralambo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:48:48 by rralambo          #+#    #+#             */
/*   Updated: 2022/11/16 11:46:58 by rralambo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		len_s;
	char		*res;

	if (s == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	if (start > len_s)
		return (ft_strdup(""));
	if (start + len < len_s)
		res = (char *)malloc((len + 1) * sizeof(char));
	else
		res = (char *)malloc((len_s - start + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = 0;
	return (res);
}

/*
int main()
{
	char src[] = "ceci est un test";
	char *dst = ft_substr(src, 5, 6);
	printf("%s\n", dst);
}*/
