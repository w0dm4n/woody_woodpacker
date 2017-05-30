/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 14:28:37 by frmarinh          #+#    #+#             */
/*   Updated: 2015/12/07 22:52:17 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *string, int c)
{
	while (*string != (char)c)
	{
		if (*string == '\0')
			return (NULL);
		string++;
	}
	return ((char *)string);
}
