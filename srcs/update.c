/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 02:56:25 by frmarinh          #+#    #+#             */
/*   Updated: 2017/06/06 02:57:22 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_stub			*alloc_stub()
{
	t_stub		*stub = malloc(sizeof(struct s_stub*));
	if (stub != NULL)
	{
		stub->text = NULL;
		stub->text_len = 0;
	}
	return (stub);
}

t_stub			*get_stub_data()
{
	int			fd		= open("stub", O_RDONLY);
	t_stub		*stub	= alloc_stub();
	if (fd != -1)
	{
		int					len				= lseek(fd, 0, SEEK_END);
		void				*buffer			= ft_mmap(fd, len);
		struct elf64_hdr*	header			= (struct elf64_hdr*) buffer;
		struct elf64_shdr	*section		= (struct elf64_shdr*) (buffer + header->e_shoff);
		char				*string_tab		= buffer + section[header->e_shstrndx].sh_offset;
		int									i = 0;
		while (i < header->e_shnum)
		{
			if (!ft_strcmp(".text", string_tab + section[i].sh_name))
			{
				stub->text_len = section[i].sh_size;
				stub->text = malloc(stub->text_len);
				ft_memcpy(stub->text, buffer + section[i].sh_offset, stub->text_len);
			}
			i++;
		}
	}
	else
		print_error(strerror(errno), true);
	return (stub);
}

void			replace_section(char *section_name, void *content, int size)
{
	t_data			*data			= get_data();
	t_section		*sections		= data->elf->sections;
	void			*base_pointer	= data->new_buffer + data->elf->header->e_shoff;
	while (sections)
	{
		if (!ft_strcmp(section_name, get_section_name(sections->data->sh_name)))
		{	
			//g_diff = size - sections->data->sh_size;
			sections->data->sh_size = size;
			sections->content = content;
			break;
		}
		sections = sections->next;
	}
}

void			update_elf()
{
	t_stub	*stub = get_stub_data();
	//replace_section(".text", stub->text, stub->text_len);
	//printf("diff : %d\n", g_diff);
}
