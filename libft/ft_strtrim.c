/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rralambo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:46:43 by rralambo          #+#    #+#             */
/*   Updated: 2022/11/16 11:54:21 by rralambo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	c_inset(char const *set, int c)
{
	int	i;

	if (set == NULL)
		return (0);
	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		begin;
	int		end;
	int		i;
	char	*res;

	begin = 0;
	if (s1 == NULL)
		return (NULL);
	while (c_inset(set, s1[begin]))
		begin++;
	end = ft_strlen(s1) - 1;
	while (c_inset(set, s1[end]) && end > begin)
		end--;
	res = (char *)malloc((end - begin + 2) * sizeof(char));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (begin <= end)
	{
		res[i] = s1[begin];
		i++;
		begin++;
	}
	res[i] = '\0';
	return (res);
}

/*
int	main()
{
	char	t1[] = "   -- ceci est un test         ";
	char	set[] = " -";
	char	*res;

	res = ft_strtrim(t1, set);
	printf("%sX\n", res);
}*/
