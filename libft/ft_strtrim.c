/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 03:31:59 by frmarinh          #+#    #+#             */
/*   Updated: 2015/12/12 04:57:15 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		ft_getstart(char const *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\n' && s[i] != '\t')
			break ;
		i++;
	}
	return (i);
}

static int		ft_getend(char const *s)
{
	int		len;

	len = (ft_strlen(s) - 1);
	while (s[len])
	{
		if (s[len] != ' ' && s[len] != '\n' && s[len] != '\t')
			break ;
		len--;
	}
	return (len + 1);
}

char			*ft_strtrim(char const *s)
{
	char	*tmp;
	int		start;
	int		end;
	int		new;

	new = 0;
	if (!(tmp = malloc(sizeof(char) * ft_strlen(s) + 1)))
		return (NULL);
	start = ft_getstart(s);
	end = ft_getend(s);
	while (start < end)
	{
		tmp[new] = s[start];
		start++;
		new++;
	}
	tmp[new] = '\0';
	return (tmp);
}
