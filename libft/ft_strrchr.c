/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 15:27:24 by frmarinh          #+#    #+#             */
/*   Updated: 2015/12/07 22:18:50 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *string, int c)
{
	unsigned char	*tmp;
	unsigned char	*iter;

	tmp = (unsigned char*)string;
	iter = NULL;
	while (*tmp)
	{
		if (*tmp == (char)c)
			iter = tmp;
		tmp++;
	}
	if (*tmp == (char)c)
		iter = tmp;
	if (iter != NULL)
		return ((char*)iter);
	else
		return (NULL);
}
