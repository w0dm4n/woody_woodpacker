/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 16:47:07 by frmarinh          #+#    #+#             */
/*   Updated: 2015/12/07 21:28:06 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *t, size_t len)
{
	int		tofind_size;
	int		boolean;
	size_t	len_reset;

	boolean = 0;
	len_reset = len;
	tofind_size = ft_strlen(t);
	if (!*t)
		return ((char*)src);
	while (len-- && *src && *t)
	{
		if (*src == *t && *t++)
			boolean++;
		else if (boolean && (*src != *t))
		{
			while (boolean && *t-- && ((len = len_reset)) && *src--)
				boolean--;
		}
		if (boolean == tofind_size)
			return ((char*)src - tofind_size + 1);
		src++;
	}
	return (NULL);
}
