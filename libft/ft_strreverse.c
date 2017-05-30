/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreverse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 23:55:49 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/30 15:07:11 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strreverse(char *str)
{
	int		i;
	int		n;
	char	*new;

	n = 0;
	if (!(new = ft_strnew(ft_strlen(str))))
		return (NULL);
	i = (ft_strlen(str) - 1);
	while (str[i])
		new[n++] = str[i--];
	new[n] = '\0';
	return (new);
}
