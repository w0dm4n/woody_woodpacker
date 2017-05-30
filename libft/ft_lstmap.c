/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 22:14:27 by frmarinh          #+#    #+#             */
/*   Updated: 2015/12/03 01:52:27 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *next;
	t_list *tmp;

	new = NULL;
	if (lst && f)
	{
		new = f(lst);
		if (!new)
			return (NULL);
		tmp = new;
		lst = lst->next;
		while (lst && lst->content && lst->content_size)
		{
			next = f(lst);
			tmp->next = next;
			tmp = next;
			lst = lst->next;
		}
	}
	return (new);
}
