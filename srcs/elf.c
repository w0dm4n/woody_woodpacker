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

	data->elf->header = (struct elf64_hdr*) data->encrypted_buffer;
	get_magic();
	get_arch();
	get_endian();
}

bool		is_elf_file()
{
	t_data			*data = get_data();
	return (ft_strcmp(ELF_MAGIC_HEXA, (char*)data->elf->magic) == 0);
}

void		save_crypted_file(char *file)
{
	t_data		*data = get_data();
	int			fd = open(file, O_RDWR | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH);
	if (fd != -1)
	{
		if ((write(fd, data->encrypted_buffer, data->len)) == -1)
			print_error(strerror(errno), true);
	}
	else
		print_error(strerror(errno), true);
}


void		change_text(struct elf64_shdr section, char *string_tab)
{
	t_data		*data = get_data();
	char		*offset = data->encrypted_buffer + section.sh_offset;
	int			i = 0;
	if (!g_text)
	{
		g_text = ft_strnew(section.sh_size);
		while (i < section.sh_size)
		{
			g_text[i] = offset[i];
			i++;
		}
		printf("Name: %s, Type value: %d, offset: %lld, size: %lld\n", (char*) (string_tab + section.sh_name), 
			section.sh_type, section.sh_offset, section.sh_size);
	}
	else
	{
		printf("Actual size %lld\n", section.sh_size);
		i = 0;
		//ft_memset(offset, 0, 445);
		while (i < 438)
		{
			//offset[i] = g_text[i];
			((char*)data->encrypted_buffer)[section.sh_offset + i] = g_text[i];
			i++;
		}
		section.sh_size = 438;
		save_crypted_file("woody");
	}
}

void		parse_section()
{
	t_data				*data = get_data();
	struct elf64_shdr	*section = (struct elf64_shdr*) (data->encrypted_buffer + data->elf->header->e_shoff);
	char				*string_tab = data->encrypted_buffer + section[data->elf->header->e_shstrndx].sh_offset;
	int					i = 1;
	while (i < data->elf->header->e_shnum)
	{
		if (!ft_strcmp((char*) (string_tab + section[i].sh_name), ".text"))
			change_text(section[i], string_tab);
		/*printf("Name: %s, Type value: %d, offset: %lld, size: %lld\n", (char*) (string_tab + section[i].sh_name), 
		section[i].sh_type, section[i].sh_offset, section[i].sh_size);
		*/
		i++;
	}
}

void		read_elf(char *file_name)
{
	t_data			*data = get_data();
	if ((data->fd = open(file_name, O_RDONLY)) == -1)
		print_error(strerror(errno), true);
	if ((data->len = lseek(data->fd, 0, SEEK_END)) <= 0)
		print_error(strerror(errno), true);
	if (!(data->file_buffer = ft_mmap(data->fd, data->len)))
		print_error(strerror(errno), true);
	if (!(data->encrypted_buffer = ft_strnew(data->len)))
		return ;
	ft_memcpy(data->encrypted_buffer, data->file_buffer, data->len);
	get_elf_header();
	if (is_elf_file())
	{
		if (data->elf->is_64)
		{
			if (data->elf->big_endian)
			{
				// hey swap me !
			}
			parse_section();
		}
		else
			print_error("The file is not a 64bit ELF file !", true);
	}
	else
		print_error("The file is not a valid ELF file", true);
}