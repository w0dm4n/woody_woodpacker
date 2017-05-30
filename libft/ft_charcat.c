/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 01:20:37 by frmarinh          #+#    #+#             */
/*   Updated: 2016/01/15 00:42:02 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_charcat(char *str, char toadd)
{
	int		i;
	char	*new;

	i = 0;
	if (!(new = malloc(sizeof(char) * (ft_strlen(str) + 2))))
		return (NULL);
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = toadd;
	new[i + 1] = '\0';
	return (new);
}
