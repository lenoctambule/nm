/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rralambo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:32:40 by rralambo          #+#    #+#             */
/*   Updated: 2022/11/22 11:46:06 by rralambo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	res;
	size_t	i;

	res = 0;
	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			res++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (res);
}

static char	*ft_strdupa2b(char const *a, char const *b)
{
	char	*res;
	size_t	i;

	i = 0;
	res = (char *)malloc(sizeof(char) * (b - a + 1));
	if (res == NULL)
		return (NULL);
	while (a < b)
	{
		res[i] = *a;
		a++;
		i++;
	}
	res[i] = '\0';
	return (res);
}

static char	**ft_freesplit(char **res, int j)
{
	while (j > 0)
	{
		free(res + j);
		j--;
	}
	return ((char **) NULL);
}

char	**ft_split(char const *s, char c)
{
	char const	*begin;
	char		**res;
	size_t		j;

	if (s == NULL)
		return (NULL);
	res = (char **)malloc(sizeof(char **) * (count_words(s, c) + 1));
	if (res == NULL)
		return (NULL);
	j = 0;
	begin = s;
	while (*s)
	{
		if (*s == c && *(s + 1) != c)
			begin = s + 1;
		else if ((*s != c && *(s + 1) == c) || *(s + 1) == '\0')
		{
			res[j] = ft_strdupa2b(begin, s + 1);
			if (res[j++] == NULL)
				return (ft_freesplit(res, j--));
		}
		s++;
	}
	res[j] = NULL;
	return (res);
}

/*
int	main(int ac, char **av)
{
	char **res = ft_split(av[1], av[2][0]);
	for (int i = 0; res[i]; i++)
		printf("%s\n", res[i]);
	return (0);
}*/
