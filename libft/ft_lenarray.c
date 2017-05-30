/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lenarray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 00:37:51 by frmarinh          #+#    #+#             */
/*   Updated: 2015/12/09 00:41:40 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_lenarray(void **array)
{
	size_t	i;
	char	**tmp;

	if (!array)
		return (0);
	i = 0;
	tmp = (char**)array;
	while (tmp[i])
		i++;
	return (i);
}
