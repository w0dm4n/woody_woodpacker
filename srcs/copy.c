/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 17:21:13 by frmarinh          #+#    #+#             */
/*   Updated: 2017/06/05 17:21:19 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		copy_segments()
{
	t_data		*data = get_data();
	struct elf64_phdr	*segment_header = data->buffer + data->elf->header->e_phoff;
	int i = 0;
	while (i < data->elf->header->e_phnum)
		new_segment(&segment_header[i++]);
}

void		copy_sections()
{
	t_data		*data = get_data();
	struct elf64_shdr	*section = (struct elf64_shdr*) (data->buffer + data->elf->header->e_shoff);
	int i = 0;
	while (i < data->elf->header->e_shnum)
	{
		new_section(&section[i], data->buffer + section[i].sh_offset);
		i++;
	}
}

void        copy_elf()
{
	t_data			*data = get_data();

	copy_segments();
	copy_sections();
	if (data->elf->big_endian)
	{
		// hey swap me !
	}
}