/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 21:35:48 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/22 23:42:41 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_base(char tmp)
{
	static char	b[16] = "0123456789abcdef";
	int			j;

	j = 0;
	while (j <= 15)
	{
		if (tmp == b[j])
			break ;
		j++;
	}
	return (j);
}

void	ft_down_let(char *tmp, const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 'A' && str[i] <= 'F')
			tmp[i] = str[i] + 32;
		else
			(tmp[i] = str[i]);
		i++;
	}
}

int		ft_atoi_base(const char *str, int str_base)
{
	int		i;
	int		minus;
	int		nb;
	char	*tmp;

	i = 0;
	minus = 1;
	nb = 0;
	while (str[i] != '\0')
		i++;
	tmp = (char*)malloc(sizeof(*tmp) * i);
	ft_down_let(tmp, str);
	i = 0;
	while (tmp[i] == ' ' || tmp[i] == '	' || tmp[i] == '\n')
		i++;
	if (tmp[i] == '-' && ((tmp[i + 1] >= 'a' && tmp[i + 1] <= 'f') ||
				(tmp[i + 1] >= '0' && tmp[i + 1] <= '9')))
	{
		minus = -1;
		i++;
	}
	while ((tmp[i] >= 'a' && tmp[i] <= 'f') || (tmp[i] >= '0' && tmp[i] <= '9'))
		nb = nb * str_base + ft_base(tmp[i++]);
	return (minus * nb);
}
