/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_writer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 10:31:31 by jguyet            #+#    #+#             */
/*   Updated: 2017/06/09 14:33:53 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

/*
 * static void     *write_header(void *ptr, t_elf *elf)
 * ----------------------
 *
 * Params :
 * void *ptr    -> ptr of buffer alloced
 * t_elf *elf   -> struct t_elf reference
 *
 * write header to ptr buffer
 * change elf->header->e_phnum (NUMBER OF TOTAL SEGMENTS)
 * change elf->header->e_shnum (NUMBER OF TOTAL SECTIONS)
 * change elf->header->e_phoff (START POINTER OF SEGMENTS)
 * change elf->header->e_shoff (START POINTER OF SECTIONS)
 * change elf->header->e_shstrndx   (INDEX OF STRING TAB)
 *
 * Return   void * buffer pointer
 */
static void     *write_header(void *ptr, t_elf *elf)
{
	//set numbers
	printf("(base)elf->header->e_phnum: %d\n", elf->header->e_phnum);
	printf("(base)elf->header->e_shnum: %d\n", elf->header->e_shnum);
	elf->header->e_phnum = elf->get_nbr_segments(elf->segments);
	elf->header->e_shnum = elf->get_nbr_sections(elf->sections);
	printf("(final)elf->header->e_phnum: %d\n", elf->header->e_phnum);
	printf("(final)elf->header->e_shnum: %d\n\n", elf->header->e_shnum);
	//set offsets
	printf("(base)elf->header->e_phoff: %d\n", elf->header->e_phoff);
	printf("(base)elf->header->e_shoff: %d\n", elf->header->e_shoff);
	elf->header->e_phoff = sizeof(struct elf64_hdr);
	elf->header->e_shoff = elf->get_offset_sections(elf);


	printf("(final)elf->header->e_phoff: %d\n", elf->header->e_phoff);
	printf("(final)elf->header->e_shoff: %d\n", elf->header->e_shoff);

    printf("(beta)elf->header->e_shoff: %d\n", elf->header->e_shoff);
	//TODO String tab
    printf("(base).shstrtab index %d\n", elf->header->e_shstrndx);
    elf->header->e_shstrndx = (unsigned short)elf->get_index_section(elf, ".shstrtab") - 1;
    printf("(final).shstrtab index %hu\n", elf->header->e_shstrndx);
	ft_memcpy(ptr, elf->header, sizeof(struct elf64_hdr));
	return (ptr);
}

/*
 * static bool	   write_segments(void *ptr, t_elf *elf)
 * ----------------------
 *
 * Params :
 * void *ptr    -> ptr of start segments zone of buffer alloced
 * t_elf *elf   -> struct t_elf reference
 *
 * write all segments (elf->segments)
 *
 * Return   bool
 *          true    -> success
 *          false   -> error
 */
static bool	   write_segments(void *ptr, t_elf *elf)
{
	t_segment	*tmp;
	int			offset;

	tmp = elf->segments;
	offset = 0;
	while (tmp)
	{
		ft_memcpy(ptr + elf->header->e_phoff + offset, tmp->data, sizeof(struct elf64_phdr));
		offset += sizeof(struct elf64_phdr);
		tmp = tmp->next;
	}
	return (true);
}

/*
 * static bool     write_sections(void *ptr, t_elf *elf)
 * ----------------------
 *
 * Params :
 * void *ptr    -> ptr of start sections zone of buffer alloced
 * t_elf *elf   -> struct t_elf reference
 *
 * write all sections and sections contents (elf->sections) and (elf->sections[?]->content)
 *
 * Return   bool
 *          true    -> success
 *          false   -> error
 */
static bool     write_sections(void *ptr, t_elf *elf)
{
	t_section	*tmp;
	int			offset;

	tmp = elf->sections;
	offset = 0;
	while (tmp)
	{
		ft_memcpy(ptr + elf->header->e_shoff + offset, tmp->data, sizeof(struct elf64_shdr));
        ft_memcpy(ptr + tmp->data->sh_offset, tmp->content, tmp->data->sh_size);
		offset += sizeof(struct elf64_shdr);
		tmp = tmp->next;
	}
	return (true);
}

/*
 * void	       *write_elf(t_elf *elf)
 * ----------------------
 *
 * Params :
 * t_elf *elf   -> struct t_elf reference
 *
 * Alloc a new Pointer by elf->len
 * write elf->header on top *ptr
 * write elf->segments after header
 * write sections_header on footer *ptr and content on center
 *
 * Return   void *ptr
 *          NULL    -> error
 */
void	       *write_elf(t_elf *elf)
{
	void	*ptr;

	if (!(ptr = (void*)malloc(elf->len * 2)))//SOUCIS TECHNIQUE SI J'ALLOUE PAS UN GROS BUFFER MALLOC M'ALLOUE PAS LA BONNE TAILLE
		return (NULL);
	ft_bzero(ptr, elf->len * 2);

	write_header(ptr, elf);
	write_segments(ptr, elf);
	write_sections(ptr, elf);
	return (ptr);
}
