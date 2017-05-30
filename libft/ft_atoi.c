/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 18:41:24 by frmarinh          #+#    #+#             */
/*   Updated: 2015/11/29 02:59:18 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(char *str)
{
	int i;
	int neg;
	int result;

	i = 0;
	neg = 0;
	result = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\r'
			|| str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-' && str[i + 1] && str[i + 1] > 47 && str[i] < 58)
			neg = 1;
		i++;
	}
	while (str[i] && str[i] > 47 && str[i] < 58)
	{
		result = result * 10;
		result += (int)str[i] - 48;
		i++;
	}
	if (neg)
		result = -result;
	return (result);
}
