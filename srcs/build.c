/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 02:10:16 by frmarinh          #+#    #+#             */
/*   Updated: 2017/06/06 02:10:22 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		save_file(char *file)
{
	t_data		*data = get_data();
	int			fd = open(file, O_RDWR | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH);
	if (fd != -1)
	{
		if ((write(fd, data->new_buffer, data->len)) == -1)
			print_error(strerror(errno), true);
	}
	else
		print_error(strerror(errno), true);
}

void					set_segments()
{
	t_data				*data			= get_data();
	t_segment			*segments		= data->elf->segments;
	int					i				= 0;
	void				*base_pointer	= data->new_buffer + data->elf->header->e_phoff;
	while (segments)
	{
		ft_memcpy(base_pointer + (sizeof(struct elf64_phdr) * i++), segments->data, sizeof(struct elf64_phdr));
		segments = segments->next;
	}
}

char				*get_section_name(int offset)
{
	t_data				*data			= get_data();
	struct elf64_shdr	*section		= (struct elf64_shdr*) (data->buffer + data->elf->header->e_shoff);
	char				*string_tab		= data->buffer + section[data->elf->header->e_shstrndx].sh_offset;
	return (string_tab + offset);
}

void				set_sections()
{
	t_data				*data			= get_data();
	t_section			*sections		= data->elf->sections;
	int					i				= 0;
	void				*base_pointer	= data->new_buffer + data->elf->header->e_shoff;
	while (sections)
	{
		ft_memcpy(base_pointer + ((sizeof(struct elf64_shdr) * i++)), sections->data, sizeof(struct elf64_shdr));

		//if (ft_strcmp(get_section_name(sections->data->sh_name), ".bss"))
		ft_memcpy(data->new_buffer + sections->data->sh_offset, sections->content, sections->data->sh_size);
		printf("%s\n", get_section_name(sections->data->sh_name));
		sections = sections->next;
	}
}

void					set_strings()
{
	t_data				*data = get_data();
	struct elf64_shdr	*section		= (struct elf64_shdr*) (data->buffer + data->elf->header->e_shoff);
	struct elf64_shdr	*string_section = &section[data->elf->header->e_shstrndx];
	ft_memcpy(data->new_buffer + string_section->sh_offset, data->buffer + string_section->sh_offset, string_section->sh_size);
}

void					build()
{
	t_data				*data = get_data();

	if (!(data->new_buffer = ft_strnew(data->len)))
		return ;
	ft_memcpy(data->new_buffer, data->elf->header, sizeof(struct elf64_hdr));
	set_segments();
	set_sections();
	set_strings();
	save_file("woody");
}