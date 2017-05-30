/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 15:57:14 by frmarinh          #+#    #+#             */
/*   Updated: 2015/12/07 21:30:45 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *src, const char *tofind)
{
	int boolean;
	int tofind_size;

	boolean = 0;
	tofind_size = ft_strlen(tofind);
	if (!*tofind)
		return ((char*)src);
	while (*src && *tofind)
	{
		if (*src == *tofind && *tofind++)
			boolean++;
		else if (boolean && (*src != *tofind))
		{
			while (boolean != 0 && *tofind--)
			{
				boolean--;
				src--;
			}
		}
		if (boolean == tofind_size)
			return ((char *)src - tofind_size + 1);
		src++;
	}
	return (NULL);
}
