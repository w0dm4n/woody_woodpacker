/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 19:51:26 by frmarinh          #+#    #+#             */
/*   Updated: 2015/12/12 04:56:25 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	char	*tmp;

	if (!(tmp = malloc(sizeof(char) * size + 1)))
		return (NULL);
	ft_bzero(tmp, (size + 1));
	return (tmp);
}
