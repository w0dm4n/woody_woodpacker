/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 12:41:28 by frmarinh          #+#    #+#             */
/*   Updated: 2015/12/12 03:14:05 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*start_itoa(unsigned int i, int len, int tmp, char *str)
{
	if (len)
		str[0] = '-';
	while (i)
	{
		str[len] = (char)(tmp / i) + '0';
		tmp = tmp - ((tmp / i) * i);
		i = i / 10;
		len++;
	}
	str[len] = '\0';
	return (str);
}

char		*ft_itoa(int c)
{
	char			*str;
	unsigned int	i;
	int				tmp;
	int				len;
	int				nega;

	nega = 0;
	if (c < 0)
	{
		nega++;
		c = -c;
	}
	i = 1;
	tmp = c;
	len = 0;
	while ((tmp = tmp / 10))
	{
		i = i * 10;
		len++;
	}
	if (!(str = ft_strnew(len + (nega ? 1 : 0) + 1)))
		return (NULL);
	len = 0;
	return (start_itoa(i, (nega ? 1 : 0), c, str));
}
