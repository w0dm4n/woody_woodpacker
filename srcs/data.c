/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 11:43:52 by frmarinh          #+#    #+#             */
/*   Updated: 2017/06/03 11:44:05 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_data			*alloc_data()
{
	if (!(g_data = (t_data*)malloc(sizeof(struct s_data))))
		return (NULL);
	if (!(g_data->elf = (t_elf*)malloc(sizeof(struct s_elf))))
		return (NULL);
	g_data->fd = 0;
	g_data->elf->is_64 = false;
	g_data->elf->little_endian = false;
	g_data->elf->big_endian = false;
	return g_data;
}

t_data			*get_data()
{
	return ((g_data) ? g_data : alloc_data());
}
