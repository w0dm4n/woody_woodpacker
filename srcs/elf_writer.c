/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_writer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 10:31:31 by jguyet            #+#    #+#             */
/*   Updated: 2017/06/09 13:29:20 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

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
