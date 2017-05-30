/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 11:53:04 by frmarinh          #+#    #+#             */
/*   Updated: 2015/12/07 21:40:28 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *str1, const void *str2, size_t n)
{
	char		*tmp1;
	const char	*tmp2;
	size_t		i;

	i = 0;
	tmp1 = str1;
	tmp2 = str2;
	while (i < n)
	{
		*tmp1++ = *tmp2++;
		i++;
	}
	return (str1);
}
