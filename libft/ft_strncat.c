/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 17:54:24 by frmarinh          #+#    #+#             */
/*   Updated: 2015/12/08 02:40:34 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	char		*dest_tmp;
	const char	*src_tmp;
	size_t		i;

	dest_tmp = dest;
	src_tmp = src;
	i = ft_strlen(dest);
	while (n)
	{
		if ((dest_tmp[i] = *src_tmp++) == 0)
			break ;
		i++;
		n--;
	}
	dest_tmp[i] = '\0';
	return (dest);
}
