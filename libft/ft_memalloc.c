/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 19:05:44 by frmarinh          #+#    #+#             */
/*   Updated: 2015/12/12 04:19:52 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void *tmp;

	if (!(tmp = (void*)malloc(sizeof(void*) * size)))
		return (NULL);
	ft_bzero(tmp, (size + 1));
	return (tmp);
}
