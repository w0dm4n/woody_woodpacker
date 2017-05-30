/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:00:29 by frmarinh          #+#    #+#             */
/*   Updated: 2015/12/07 22:54:51 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *str1, const void *str2, int c, size_t n)
{
	unsigned char	*str1_tmp;
	unsigned char	*str2_tmp;
	size_t			i;

	if (!n)
		return (NULL);
	i = 0;
	str1_tmp = (unsigned char*)str1;
	str2_tmp = (unsigned char*)str2;
	while (i < n)
	{
		str1_tmp[i] = str2_tmp[i];
		if (str1_tmp[i] == (unsigned char)c)
			return (&str1_tmp[i + 1]);
		i++;
	}
	return (NULL);
}
