/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 23:13:29 by frmarinh          #+#    #+#             */
/*   Updated: 2016/01/21 01:46:43 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	int i;
	int len_s1;
	int len_s2;

	i = 0;
	if (!s1 || !s2)
		return (0);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (s1 && s2)
	{
		while (*s1 && *s2 && *s1++ == *s2++)
			i++;
	}
	else
		return (0);
	if (i == len_s1 && i == len_s2)
		return (1);
	else
		return (0);
}
