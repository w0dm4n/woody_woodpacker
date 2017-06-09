/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 11:51:04 by frmarinh          #+#    #+#             */
/*   Updated: 2017/06/09 13:42:51 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int		get_nbr_segments(struct s_segment *segments)
{
	struct s_segment	*tmp;
	int					res;

	res = 0;
	tmp = segments;
	while (tmp)
	{
		res++;
		tmp = tmp->next;
	}
	return (res);
}

int		get_nbr_sections(struct s_section *sections)
{
	struct s_section	*tmp;
	int					res;

	res = 0;
	tmp = sections;
	while (tmp)
	{
		res++;
		tmp = tmp->next;
	}
	return (res);
}

int		get_offset_sections(t_elf *elf)
{
	struct s_section	*tmp_sec;
	int		offset;

	offset = 0;
	tmp_sec = elf->sections;
	while (tmp_sec)
	{
		offset = tmp_sec->data->sh_offset + tmp_sec->data->sh_size + 1;
		tmp_sec = tmp_sec->next;
	}
	return (offset);
}

int		get_index_section(t_elf *elf, char *name)
{
	t_section	*tmp;
	int			index;

	tmp = elf->sections;
	index = 0;
	while (tmp)
	{
		index++;
		if (ft_strcmp(name, tmp->name) == 0)
		{
			return (index);
		}
		tmp = tmp->next;
	}
	return (-1);
}

t_section	*get_section(t_elf *elf, char *name)
{
	t_section	*tmp;

	tmp = elf->sections;
	while (tmp)
	{
		if (ft_strcmp(name, tmp->name) == 0)
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

t_segment	*get_segment_by_section(t_elf *elf, t_section *section)
{
	t_segment	*tmp;

	tmp = elf->segments;
	while (tmp)
	{
		if ((section->data->sh_addr) >= tmp->data->p_vaddr
			&& section->data->sh_addr < (tmp->data->p_vaddr + tmp->data->p_memsz))
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	printf("NULL");
	return (NULL);
}

t_segment	*get_segment_type(t_elf *elf, int type)
{
	t_segment	*tmp;

	tmp = elf->segments;
	while (tmp)
	{
		if (tmp->data->p_type == type)
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

t_section	**get_sections_segment(t_elf *elf, t_segment *segment)
{
	t_section	*tmp;
	t_section	**result;
	int			size;
	int			i;

	tmp = elf->sections;
	size = 0;
	i = 0;
	while (tmp)
	{
		if (tmp->data->sh_addr > segment->data->p_vaddr &&\
			tmp->data->sh_addr < (segment->data->p_vaddr + segment->data->p_memsz))
		{
			size++;
		}
		tmp = tmp->next;
	}
	if (!(result = (t_section **)malloc(sizeof(t_section*) * (size + 1))))
		return (NULL);
	tmp = elf->sections;
	while (tmp)
	{
		if (tmp->data->sh_addr > segment->data->p_vaddr &&\
			tmp->data->sh_addr < (segment->data->p_vaddr + segment->data->p_memsz))
		{
			result[i] = tmp;
			i++;
		}
		tmp = tmp->next;
	}
	result[i] = NULL;
	return (result);
}

t_elf		*alloc_elf(void)
{
	t_elf	*elf;

	if (!(elf = (t_elf*)malloc(sizeof(struct s_elf))))
		return (NULL);
	elf->is_64 = false;
	elf->little_endian = false;
	elf->big_endian = false;
	elf->segments = NULL;
	elf->sections = NULL;
	elf->string_tab = NULL;
	elf->len = 0;
	elf->buffer = NULL;
	elf->get_section = get_section;
	elf->get_nbr_segments = get_nbr_segments;
	elf->get_nbr_sections = get_nbr_sections;
	elf->get_offset_sections = get_offset_sections;
	elf->get_index_section = get_index_section;
	elf->get_segment_type = get_segment_type;
	elf->get_sections_segment = get_sections_segment;
	elf->get_segment_by_section = get_segment_by_section;
	return elf;
}
