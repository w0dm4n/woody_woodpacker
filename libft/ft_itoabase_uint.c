/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoabase_uint.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 18:23:02 by frmarinh          #+#    #+#             */
/*   Updated: 2017/02/28 18:30:37 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoabase_uint(unsigned long int nbr, char *base)
{
	char				*res;
	unsigned long int	size;
	unsigned long int	len;
	unsigned long int	tmp;

	tmp = nbr;
	len = 1;
	size = 0;
	while ((tmp = tmp / ft_strlen(base)))
	{
		len = len * ft_strlen(base);
		size++;
	}
	tmp = nbr;
	res = (char*)malloc(sizeof(char) * (size + 1));
	size = 0;
	while (len)
	{
		res[size] = base[(tmp / len)];
		tmp = tmp - ((tmp / len) * len);
		len = len / ft_strlen(base);
		size++;
	}
	res[size] = '\0';
	return (res);
}
