/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 10:31:20 by jguyet            #+#    #+#             */
/*   Updated: 2017/06/09 15:24:54 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

/*
 * static void		load_elf_magic(t_elf *elf)
 * ----------------------
 *
 * set 4octet of MAGIC executable linkable on magic buffer (elf->magic)
 *
 * Return   void
 */
static void		   load_elf_magic(t_elf *elf)
{
	char	*value = NULL;
	char	*save_pointer = NULL;
	int		i = 0;

	if (!(value = malloc(MAGIC_LEN * 2)))
		return ;
	save_pointer = value;
	ft_bzero(elf->magic, MAGIC_LEN * 2);
	while (i < MAGIC_LEN)
	{
		asprintf(&value, "%x", elf->header->e_ident[i++]);
		ft_strncat((char*) elf->magic, value, 2);
		value += 2;
	}
	free(save_pointer);
}

/*
 * static void		load_elf_arch(t_elf *elf)
 * ----------------------
 *
 * if is executable linkable 64 bits set elf->is_64 at true
 *
 * Return   void
 */
static void		   load_elf_arch(t_elf *elf)
{
	int				arch = elf->header->e_ident[4];
	elf->is_64 = (arch == ARCH_64) ? true : false;
}

/*
 * static void      load_elf_bits_order(t_elf *elf)
 * ----------------------
 *
 * Function for load a bits_order indication
 * (elf->little_endian and elf->big_endian)
 *
 * Return   void
 */
static void		   load_elf_bits_order(t_elf *elf)
{
	int				endian = elf->header->e_ident[5];

	if (endian == L_ENDIAN)
		elf->little_endian = true;
	else if (endian == B_ENDIAN)
		elf->big_endian = true;
}

/*
 * static bool      load_elf_header(t_elf *elf)
 * ----------------------
 *
 * Function for load and alloc one fresh copy Elf64_header
 * by elf->buffer before loaded
 * , load a elf->magic
 * , load a elf->is_64
 * , load a bits_order indication (elf->little_endian and elf->big_endian)
 *
 * Return   bool
 *          false -> error of malloc
 *          true -> loaded with success
 */
static bool		   load_elf_header(t_elf *elf)
{
	struct elf64_hdr* header = (struct elf64_hdr*)elf->buffer;

	if (!(elf->header = malloc(sizeof(struct elf64_hdr))))
		return (false);
	ft_bzero(elf->header, sizeof(struct elf64_hdr));
	ft_memcpy(elf->header, header, sizeof(struct elf64_hdr));

	load_elf_magic(elf);
	load_elf_arch(elf);
	load_elf_bits_order(elf);
	return (true);
}

/*
 * static bool		is_elf_file(const t_elf *elf)
 * ----------------------
 *
 * Compare if ELF_MAGIC is equal with medium magic ELF
 *
 * Return   bool
 *          false -> is not a elf_file
 *          true -> is elf_file
 */
static bool		   is_elf_file(const t_elf *elf)
{
	return (ft_strcmp(ELF_MAGIC_HEXA, (char*)elf->magic) == 0);
}

/*
 * static t_elf		*load_section_name(t_elf *elf)
 * ----------------------
 *
 * Function for add a pointer "ptr" of String_tab ELF
 * "String_tab ELF" Contain all Section names
 *
 * Return   t_elf*
 */
static t_elf		*load_section_name(t_elf *elf)
{
	struct elf64_shdr	*section;
	char				*string_tab;

    section = (struct elf64_shdr*) (elf->buffer + elf->header->e_shoff);
    string_tab = elf->buffer + section[elf->header->e_shstrndx].sh_offset;
	elf->string_tab = string_tab;
	return (elf);
}

/*
 * static void		add_segment(t_elf *elf, t_segment *segment)
 * ----------------------
 *
 * Function for add "t_segment *segment" to end list elf->segments
 *
 * Return   void
 */
static void			add_segment(t_elf *elf, t_segment *segment)
{
	t_segment	*tmp;

	tmp = elf->segments;
	if (elf->segments != NULL)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = segment;
		segment->prev = tmp;
	}
	else
		elf->segments = segment;
}

/*
 * static t_elf		*load_segments(t_elf *elf)
 * ----------------------
 *
 * Function for load and alloc fresh Segments_header
 * by elf->buffer before loaded
 *
 * Return   t_elf*
 *          elf -> NULL Error Malloc or elf->buffer as NULL
 */
static t_elf		*load_segments(t_elf *elf)
{
	struct elf64_phdr	*segments;
	struct s_segment	*segment;
	int					i;

	i = 0;
	if (elf->buffer == NULL)
		return (NULL);
	segments = elf->buffer + elf->header->e_phoff;
    printf("[%10s] ----------SEGMENTS---------->\n", elf->name);
	while (i < elf->header->e_phnum)
	{
		if (!(segment = malloc(sizeof(struct s_segment))))
			return (NULL);
		if (!(segment->data = malloc(sizeof(struct elf64_phdr))))
			return (NULL);
		//Load Segment Header
		ft_bzero(segment->data, sizeof(struct elf64_phdr));
		ft_memcpy(segment->data, &segments[i], sizeof(struct elf64_phdr));
		segment->prev = NULL;
		segment->next = NULL;
        segment->id = i;
        printf("[%10s] |    segment [%d]                      addr: %8llu  size: %10llu  type: ", elf->name, segment->id, segment->data->p_vaddr, segment->data->p_memsz);

        if (segment->data->p_type == PT_NULL)
            printf("PT_NULL\n");
        else if (segment->data->p_type == PT_LOAD)
            printf("PT_LOAD\n");
        else if (segment->data->p_type == PT_DYNAMIC)
            printf("PT_DYNAMIC\n");
        else if (segment->data->p_type == PT_INTERP)
            printf("PT_INTERP\n");
        else if (segment->data->p_type == PT_NOTE)
            printf("PT_NOTE\n");
        else if (segment->data->p_type == PT_SHLIB)
            printf("PT_SHLIB\n");
        else if (segment->data->p_type == PT_PHDR)
            printf("PT_PHDR\n");
        else if (segment->data->p_type == PT_TLS)
            printf("PT_TLS\n");
        else if (segment->data->p_type == PT_LOOS)
            printf("PT_LOOS\n");
        else if (segment->data->p_type == PT_HIOS)
            printf("PT_HIOS\n");
        else if (segment->data->p_type == PT_LOPROC)
            printf("PT_LOPROC\n");
        else if (segment->data->p_type == PT_HIPROC)
            printf("PT_HIPROC\n");
        else if (segment->data->p_type == PT_GNU_EH_FRAME)
            printf("PT_GNU_EH_FRAME\n");
        else
            printf("UNKNOW TYPE ID[%d]\n", segment->data->p_type);
		add_segment(elf, segment);
		i++;
	}
	return (elf);
}

/*
 * static void      add_section(t_elf *elf, t_section *section)
 * ----------------------
 *
 * Function for add "t_section *section" to end list elf->sections
 *
 * Return   void
 */
static void			add_section(t_elf *elf, t_section *section)
{
	t_section *tmp;

	tmp = elf->sections;
	if (elf->sections != NULL)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = section;
		section->prev = tmp;
	}
	else
		elf->sections = section;
}

/*
 * static t_elf	    *load_sections(t_elf *elf)
 * ----------------------
 *
 * Function for load and alloc fresh Sections_header and content_section
 * by elf->buffer before loaded
 *
 * t_elf *elf   struct elf
 * Return   t_elf*
 *          elf -> NULL Error Malloc or elf->buffer as NULL
 */
static t_elf	   *load_sections(t_elf *elf)
{
	struct elf64_shdr	*sections;
	struct s_section	*section;
	int					i;

	i = 0;
	if (elf->buffer == NULL)
		return (NULL);
	sections = (struct elf64_shdr*) (elf->buffer + elf->header->e_shoff);
    printf("[%10s] ----------SECTIONS---------->\n", elf->name);
	while (i < elf->header->e_shnum)
	{
		if (!(section = malloc(sizeof(struct s_section))))
			return (NULL);
		if (!(section->data = malloc(sizeof(struct elf64_shdr))))
			return (NULL);
		if (!(section->content = malloc(sections[i].sh_size)))
			return (NULL);
		//Load Section Header
		ft_bzero(section->data, sizeof(struct elf64_shdr));
		ft_memcpy(section->data, &sections[i], sizeof(struct elf64_shdr));
		//Load Section Content
		ft_bzero(section->content, sections[i].sh_size);
		ft_memcpy(section->content, elf->buffer + sections[i].sh_offset, sections[i].sh_size);
		section->prev = NULL;
		section->next = NULL;
		section->name = ft_strdup(elf->string_tab + sections[i].sh_name);
        section->parent = elf->get_segment_by_section(elf, section);
        printf("[%10s] |    [parent segment_%d]    section %-15s    size: %10llu\n", elf->name, section->parent->id, section->name, section->data->sh_size);
		add_section(elf, section);
		i++;
	}
	return (elf);
}

/*
 * t_elf		*read_elf(const char *file_name);
 * ----------------------
 *
 * const char *file_name (Linux executable filename)
 *
 * open filename ON READ_MODE, read all bytes of file
 * copy all information to the fresh Struct t_elf*
 * and return result.
 *
 * Return   t_elf*
 *          elf -> NULL Error Malloc
 */
t_elf           *read_elf(const char *file_name)
{
	t_elf	*elf;
	int		fd;

	if (!(elf = alloc_elf()))
		return (NULL);
	if ((fd = open(file_name, O_RDONLY)) == -1)
		print_error(strerror(errno), true);
	if ((elf->len = lseek(fd, 0, SEEK_END)) <= 0)
		print_error(strerror(errno), true);
	if (!(elf->buffer = ft_mmap(fd, elf->len)))
		print_error(strerror(errno), true);
    elf->name = ft_strdup(file_name);
    printf("-------------------LOAD-[%10s]------------------>\n", elf->name);
	//LOAD ELF HEADER
	load_elf_header(elf);
	if (is_elf_file(elf))
	{
		if (elf->is_64)
		{
			load_section_name(elf);
			load_segments(elf);
			load_sections(elf);
		}
		else
			print_error("The file is not a 64bit ELF file !", true);
	}
	else
		print_error("The file is not a valid ELF file", true);
    printf("<-------------------[%10s]-LOADED------------------\n", elf->name);
	return (elf);
}
