/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 06:16:15 by frmarinh          #+#    #+#             */
/*   Updated: 2015/12/12 05:01:07 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		where(char const *s, int pos, char c)
{
	int i;

	i = 0;
	while (s[pos])
	{
		if (pos == 0)
			if (s[pos] != c)
				return (pos);
		if (s[pos] == c)
		{
			i++;
			break ;
		}
		pos++;
	}
	return ((pos + i));
}

static int		char_nbr(char const *s, char c)
{
	int i;
	int nbr;

	i = 0;
	nbr = 0;
	while (s[i])
	{
		if (s[i] == c || s[i + 1] == '\0')
			nbr++;
		i++;
	}
	return (nbr);
}

static int		next(char const *s, int pos, char c)
{
	int i;

	i = 0;
	while (s[pos])
	{
		if (s[pos] != c)
			pos++;
		else
			break ;
		i++;
	}
	return (pos);
}

static char		*get_from(char const *s, int start, int end)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!(tmp = ft_strnew(ft_strlen(s))))
		return (NULL);
	while (start < end)
	{
		tmp[i] = s[start];
		i++;
		start++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char			**ft_strsplit(char const *s, char c)
{
	int		pos;
	int		nbr;
	char	*res;
	char	**tmp;
	int		occurence;

	pos = 0;
	occurence = 0;
	if (!(res = ft_strnew(ft_strlen(s))))
		return (NULL);
	nbr = char_nbr(s, c) + 1;
	if (!(tmp = malloc(sizeof(char) * (ft_strlen(s) * ft_strlen(s)))))
		return (NULL);
	while (nbr-- > 0)
	{
		pos = where(s, pos, c);
		res = get_from(s, pos, next(s, pos, c));
		if (res[0])
			tmp[occurence++] = res;
		if (pos == 0)
			pos++;
	}
	tmp[occurence] = NULL;
	return (tmp);
}
