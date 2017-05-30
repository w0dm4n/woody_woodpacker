/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 10:37:31 by frmarinh          #+#    #+#             */
/*   Updated: 2015/12/10 23:26:57 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t length)
{
	unsigned char	*tmp;

	tmp = (unsigned char *)str;
	while (length)
	{
		*tmp++ = (unsigned char)c;
		length--;
	}
	return (str);
}
