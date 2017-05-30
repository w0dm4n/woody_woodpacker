/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strposition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 04:14:06 by frmarinh          #+#    #+#             */
/*   Updated: 2015/12/08 04:21:30 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strposition(char *from, char *tofind)
{
	size_t	i;
	size_t	occur;
	size_t	i_2;

	i = 0;
	occur = 0;
	i_2 = 0;
	while (from[i])
	{
		if (from[i] == tofind[i_2])
		{
			occur++;
			i_2++;
		}
		if (occur == ft_strlen(tofind))
			return (i);
		if (from[i + 1] != tofind[i_2])
		{
			i_2 = 0;
			occur = 0;
		}
		i++;
	}
	return (i);
}
