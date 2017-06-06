/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 11:51:04 by frmarinh          #+#    #+#             */
/*   Updated: 2017/06/03 11:51:11 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		get_magic()
{
	t_data	*data = get_data();
	char	*value = NULL;
	char	*save_pointer = NULL;
	int		i = 0;

	if (!(value = malloc(MAGIC_LEN * 2)))
		return ;
	save_pointer = value;
	ft_bzero(data->elf->magic, MAGIC_LEN * 2);
	while (i < MAGIC_LEN)
	{
		asprintf(&value, "%x", data->elf->header->e_ident[i++]);
		ft_strncat((char*) data->elf->magic, value, 2);
		value += 2;
	}
	free(save_pointer);
}

void		get_arch()
{
	t_data			*data = get_data();
	int				arch = data->elf->header->e_ident[4];
	data->elf->is_64 = (arch == ARCH_64) ? true : false;
}

void		get_endian()
{
	t_data			*data = get_data();
	int				endian = data->elf->header->e_ident[5];
	if (endian == L_ENDIAN)
		data->elf->little_endian = true;
	else if (endian == B_ENDIAN)
		data->elf->big_endian = true;
}

void		get_elf_header()
{
	t_data			*data = get_data();
	struct elf64_hdr* header = (struct elf64_hdr*) data->buffer;
	data->elf->header = malloc(sizeof(struct elf64_hdr));
	
	ft_memcpy(data->elf->header, header, sizeof(struct elf64_hdr));
	get_magic();
	get_arch();
	get_endian();
}

bool		is_elf_file()
{
	t_data			*data = get_data();
	return (ft_strcmp(ELF_MAGIC_HEXA, (char*)data->elf->magic) == 0);
}

void		read_elf(char *file_name)
{
	t_data			*data = get_data();
	if ((data->fd = open(file_name, O_RDONLY)) == -1)
		print_error(strerror(errno), true);
	if ((data->len = lseek(data->fd, 0, SEEK_END)) <= 0)
		print_error(strerror(errno), true);
	if (!(data->buffer = ft_mmap(data->fd, data->len)))
		print_error(strerror(errno), true);
	get_elf_header();
	if (is_elf_file())
	{
		if (data->elf->is_64)
		{
			copy_elf();
			build();
		}
		else
			print_error("The file is not a 64bit ELF file !", true);
	}
	else
		print_error("The file is not a valid ELF file", true);
}