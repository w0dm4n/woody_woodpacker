/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdelchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 04:23:48 by frmarinh          #+#    #+#             */
/*   Updated: 2015/12/08 21:41:58 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static	char	*del_char(char *str, char c)
{
	char	*tmp;
	size_t	i;
	size_t	i_2;

	i = 0;
	i_2 = 0;
	tmp = malloc(sizeof(char*) * ft_strlen(str));
	while (str[i])
	{
		if (str[i] != c)
		{
			tmp[i_2] = str[i];
			i_2++;
		}
		i++;
	}
	return (tmp);
}

char			*ft_strdelchar(char *str, char c)
{
	size_t	i;
	char	*tmp;

	i = 0;
	if (!c || !str)
		return (NULL);
	tmp = malloc(sizeof(char*) * ft_strlen(str));
	tmp = ft_strcpy(tmp, str);
	while (str[i])
	{
		if (str[i] == c)
			tmp = del_char(str, c);
		i++;
	}
	return (tmp);
}
