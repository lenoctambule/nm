/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rralambo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:03:55 by rralambo          #+#    #+#             */
/*   Updated: 2022/11/23 16:10:29 by rralambo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ite;
	t_list	*last;

	if (lst == NULL || *lst == NULL || del == NULL)
		return ;
	ite = (*lst)->next;
	last = *lst;
	while (ite != NULL)
	{
		ft_lstdelone(last, del);
		last = ite;
		ite = ite->next;
	}
	ft_lstdelone(last, del);
	*lst = NULL;
}
