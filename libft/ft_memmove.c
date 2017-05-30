/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:25:30 by frmarinh          #+#    #+#             */
/*   Updated: 2015/12/08 00:45:22 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memmove(void *str1, const void *str2, size_t n)
{
	char		*str1_tmp;
	const char	*str2_tmp;

	str1_tmp = str1;
	str2_tmp = str2;
	if (str2_tmp < str1_tmp)
	{
		str1_tmp += n;
		str2_tmp += n;
		while (n--)
			*--str1_tmp = *--str2_tmp;
	}
	else if (str2_tmp != str1_tmp)
		while (n--)
			*str1_tmp++ = *str2_tmp++;
	return (str1);
}
