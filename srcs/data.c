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
	g_data->elf->segments = NULL;
	g_data->elf->sections = NULL;
	return g_data;
}

t_data			*get_data()
{
	return ((g_data) ? g_data : alloc_data());
}

t_section		*get_sections()
{
	return (g_data->elf->sections);
}

t_segment		*get_segments()
{
	return (g_data->elf->segments);
}

void			add_segment(t_segment *segment)
{
	t_segment	*segments = g_data->elf->segments;
	if (segments)
	{
		while (segments->next)
			segments = segments->next;
		segments->next = segment;
		segment->prev = segments;
	}
	else
		g_data->elf->segments = segment;
}

void			add_section(t_section *section)
{
	t_section	*sections = g_data->elf->sections;
	if (sections)
	{
		while (sections->next)
			sections = sections->next;
		sections->next = section;
		section->prev = sections;
	}
	else
		g_data->elf->sections = section;
}

void		new_segment(struct elf64_phdr	*data)
{
	t_segment			*segment = malloc(sizeof(struct s_segment));
	struct elf64_phdr	*new = malloc(sizeof(struct elf64_phdr));
	ft_memcpy(new, data, sizeof(struct elf64_phdr));
	segment->data = new;
	segment->prev = NULL;
	segment->next = NULL;
	add_segment(segment);
}

void			new_section(struct elf64_shdr	*data, void *buffer)
{
	t_section			*section = malloc(sizeof(struct s_section));
	struct elf64_shdr	*new = malloc(sizeof(struct elf64_shdr));
	void				*new_buffer = malloc(data->sh_size);

	ft_memcpy(new_buffer, buffer, data->sh_size);
	ft_memcpy(new, data, sizeof(struct elf64_shdr));
	section->data = new;
	section->content = new_buffer;
	section->prev = NULL;
	section->next = NULL;
	add_section(section);
}