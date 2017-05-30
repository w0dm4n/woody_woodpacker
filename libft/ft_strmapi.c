/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 23:04:32 by frmarinh          #+#    #+#             */
/*   Updated: 2015/12/12 04:41:12 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *str, char (*f)(unsigned int, char))
{
	unsigned int		i;
	char				*tmp;

	i = 0;
	if (!str || !f)
		return (NULL);
	if (!(tmp = (char *)malloc(sizeof(char) * ft_strlen(str) + 1)))
		return (NULL);
	while (str[i])
	{
		tmp[i] = f(i, str[i]);
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
