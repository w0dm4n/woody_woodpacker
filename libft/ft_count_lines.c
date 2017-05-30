/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_lines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 04:56:35 by frmarinh          #+#    #+#             */
/*   Updated: 2016/01/07 05:32:54 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_lines(char *buffer)
{
	int i;
	int lines;

	i = 0;
	lines = 1;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			lines++;
		i++;
	}
	return (lines);
}
