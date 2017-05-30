/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 02:41:28 by frmarinh          #+#    #+#             */
/*   Updated: 2015/12/08 21:37:00 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char		*replace_occur(int place, char *tor, size_t size, char *tos)
{
	char	*tmp;
	size_t	i;
	size_t	i_2;

	i = 0;
	i_2 = 0;
	place = place - (ft_strlen(tos) - 1);
	size = place + (ft_strlen(tos));
	tmp = malloc(sizeof(char*) * ft_strlen(tor));
	while (tor[i])
	{
		if (i >= (size_t)(place) && i < (size))
		{
			tmp[i] = tos[i_2];
			i_2++;
		}
		else
			tmp[i] = tor[i];
		i++;
	}
	return (tmp);
}

char			*ft_str_replace(char *toreplace, char *tof, char *toset)
{
	char	*tmp;
	size_t	i;
	size_t	occur;
	size_t	i_2;

	i = 0;
	occur = 0;
	i_2 = 0;
	tmp = malloc(sizeof(char*) * ft_strlen(toreplace));
	tmp = ft_strcpy(tmp, toreplace);
	while (toreplace[i])
	{
		if (toreplace[i] == tof[i_2] && (i_2 = i_2 + 1))
			occur++;
		if (occur == ft_strlen(tof))
			tmp = replace_occur(i, tmp, (i + ft_strlen(toset)), toset);
		if (toreplace[i + 1] != tof[i_2])
		{
			i_2 = 0;
			occur = 0;
		}
		i++;
	}
	return (tmp);
}
