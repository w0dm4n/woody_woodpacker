/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 11:51:04 by frmarinh          #+#    #+#             */
/*   Updated: 2017/06/09 15:11:04 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

/*
 * int		get_nbr_segments(struct s_segment *segments)
 * ----------------------
 *
 * Params:
 * struct s_segment *segments (SEGMENTS TAB CHAINE)
 *
 * count all segments and return total size
 *
 * Return   int total
 */
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

/*
 * int		get_nbr_sections(struct s_section *sections)
 * ----------------------
 *
 * Params:
 * struct s_section *sections (SECTIONS TAB CHAINE)
 *
 * count all sections and return total size
 *
 * Return   int total
 */
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

/*
 * int		get_offset_sections(t_elf *elf)
 * ----------------------
 *
 * Params:
 * t_elf *elf
 *
 * select final struc s_section and return section offset + size + 1
 * offset of start header sections zone
 *
 * Return   int offset
 *          0    -> not found
 */
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

/*
 * int		get_index_section(t_elf *elf, char *name)
 * ----------------------
 *
 * Params:
 * t_elf *elf
 * char *search name
 *
 * Search section by name and return index in tab sections
 *
 * Return   int index
 *          -1    -> not found
 */
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

/*
 * t_section	*get_section(t_elf *elf, char *name)
 * ----------------------
 *
 * Params:
 * t_elf *elf
 * char *search name
 *
 * Search section by name and return pointer t_segment
 *
 * Return   t_section	*
 *          NULL    -> not found
 */
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

/*
 * t_segment	*get_segment_by_section(t_elf *elf, t_section *section)
 * ----------------------
 *
 * Params:
 * t_elf *elf
 * t_section *section (ref)
 *
 * Search on elf->segments a first segment wich section->sh_addr is in segment
 * and return pointer t_segment
 *
 * Return   t_segment	*
 *          NULL    -> not found
 */
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
	return (NULL);
}

/*
 * t_segment	*get_segment_type(t_elf *elf, int type)
 * ----------------------
 *
 * Params:
 * t_elf *elf
 * int type
 *		PT_NULL    			0
 *		PT_LOAD    			1
 *		PT_DYNAMIC 			2
 *		PT_INTERP  			3
 *		PT_NOTE    			4
 *		PT_SHLIB   			5
 *		PT_PHDR    			6
 *		PT_TLS     			7
 *		PT_LOOS    			0x60000000
 *		PT_HIOS    			0x6fffffff
 *		PT_LOPROC  			0x70000000
 *		PT_HIPROC  			0x7fffffff
 *		PT_GNU_EH_FRAME		0x6474e550
 *
 * Search on elf->segments a first segment wich type equal arg type
 * and return pointer t_segment
 *
 * Return   t_segment	*
 *          NULL    -> not found
 */
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

/*
 * t_section	**get_sections_segment(t_elf *elf, t_segment *segment)
 * ----------------------
 *
 * Params:
 * t_elf *elf
 * t_segment *segment (ref)
 *
 * Search all sections contained by t_segment *segment
 * and create a new tab and set all pointers who point in section
 * finished by null case
 *
 * Return   t_section	**tab
 *          NULL    -> error
 */
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

/*
 * t_elf		*alloc_elf(void)
 * ----------------------
 *
 * Alloc a new t_elf and set all values and pointers
 *
 * Return   t_elf *ptr
 *          NULL    -> error
 */
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
