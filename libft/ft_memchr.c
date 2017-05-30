/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 15:15:39 by frmarinh          #+#    #+#             */
/*   Updated: 2015/12/13 00:01:20 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*str_tmp;
	unsigned char	c_tmp;

	str_tmp = (unsigned char*)str;
	c_tmp = (unsigned char)c;
	while (n)
	{
		if (*str_tmp == c_tmp)
			return (str_tmp);
		str_tmp++;
		n--;
	}
	return (NULL);
}
