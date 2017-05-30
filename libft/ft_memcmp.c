/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 16:50:30 by frmarinh          #+#    #+#             */
/*   Updated: 2015/12/08 02:41:00 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	unsigned char	*tmp_str1;
	unsigned char	*tmp_str2;
	size_t			i;

	tmp_str1 = (unsigned char *)str1;
	tmp_str2 = (unsigned char *)str2;
	i = 0;
	while (i < n)
	{
		if (tmp_str1[i] != tmp_str2[i] && (tmp_str1[i] || tmp_str2[i]))
			return (tmp_str1[i] - tmp_str2[i]);
		i++;
	}
	return (0);
}
