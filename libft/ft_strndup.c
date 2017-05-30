/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 22:49:11 by frmarinh          #+#    #+#             */
/*   Updated: 2016/01/08 22:54:34 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *string, size_t size)
{
	size_t	i;
	char	*tmp;

	i = 0;
	if (!(tmp = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (i == size)
	{
		tmp[i] = string[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
