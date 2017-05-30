/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 20:48:05 by frmarinh          #+#    #+#             */
/*   Updated: 2015/12/12 04:39:23 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *str, char (*f)(char))
{
	int		i;
	char	*tmp;

	if (!str || !f)
		return (NULL);
	i = 0;
	if (!(tmp = (char *)malloc(sizeof(char) * ft_strlen(str) + 1)))
		return (NULL);
	while (str[i])
	{
		tmp[i] = f(str[i]);
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
