/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 06:08:58 by frmarinh          #+#    #+#             */
/*   Updated: 2017/06/09 15:20:13 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		*ft_mmap(int fd, size_t size)
{
	return (mmap(0, size, PROT_READ, MAP_SHARED, fd, 0));
}

void		print_error(char *error, bool should_exit)
{
	printf("Woody Woodpecker is telling you: %s\n", error);
	if (should_exit)
		exit(should_exit);
}

void		save_file(char *file, void	*content, int size)
{
	int			fd = open(file, O_RDWR | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH);
	if (fd != -1)
	{
		if ((write(fd, content, size)) == -1)
			print_error(strerror(errno), true);
	}
	else
		print_error(strerror(errno), true);
}

int			main(int argc, char **argv)
{
	t_elf *ofile;
	t_elf *ofile_2;

	if (argc == 3)
	{
		ofile = read_elf(argv[1]);
		ofile_2 = read_elf(argv[2]);

		t_segment *segload = ofile->get_segment_type(ofile, PT_LOAD);
		t_section **seg_secs = ofile->get_sections_segment(ofile, segload);

		int i = 0;
		while (seg_secs[i])
		{
			printf("sectionName : %s\n", seg_secs[i]->name);
			i++;
		}

		replace_section(ofile_2->get_section(ofile_2, ".text"), ofile);
		//replace_section(ofile_2->get_section(ofile_2, ".rodata"), ofile);
		//replace_section(ofile_2->get_section(ofile_2, ".bss"), ofile);

		void	*content = write_elf(ofile);

		save_file("copy", content, ofile->len);
		//TODO process
	}
	else
		printf("Woody Woodpecker informs you that you need to give him an executable to encrypt ! \n");
	return (0);
}
