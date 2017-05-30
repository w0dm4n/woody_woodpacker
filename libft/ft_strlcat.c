/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 13:53:43 by frmarinh          #+#    #+#             */
/*   Updated: 2015/12/12 04:16:08 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t		n;
	size_t		dlen;
	char		*dest_cpy;
	const char	*src_cpy;

	n = size;
	src_cpy = src;
	dest_cpy = dest;
	while (*dest_cpy != '\0' && n--)
		dest_cpy++;
	dlen = dest_cpy - dest;
	n = size - dlen;
	if (n == 0)
		return (dlen + ft_strlen(src));
	while (*src_cpy != '\0')
	{
		if (n != 1)
		{
			*dest_cpy++ = *src_cpy;
			n--;
		}
		src_cpy++;
	}
	*dest_cpy = '\0';
	return (dlen + (src_cpy - src));
}
