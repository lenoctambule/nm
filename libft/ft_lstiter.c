/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rralambo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:15:25 by rralambo          #+#    #+#             */
/*   Updated: 2022/11/23 15:35:24 by rralambo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (f == NULL)
		return ;
	while (lst != NULL)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}

/*
void	printnode(t_list *lst)
{
	printf("%d\n", *(int *)(lst->content));
}

void	del(t_list *l)
{
	l->content = 0;
}

int	main()
{
	int	c[] = {0,1,2,3,4,5,6,7,8,9};
	t_list	*t;
	for (int i = 0; i < 10; i++)
	{
		ft_lstadd_back(&t, ft_lstnew(&c[i]));
	}
	printf("last : ");
	printnode(ft_lstlast(t));
	ft_lstiter(t, printnode);
	ft_lstclear(t, del);
}*/
