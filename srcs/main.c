/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 06:08:58 by frmarinh          #+#    #+#             */
/*   Updated: 2017/05/30 06:10:33 by frmarinh         ###   ########.fr       */
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

int			main(int argc, char **argv)
{
	if (argc == 2)
	{
		read_elf("stub");
		read_elf(argv[1]);
	}
	else
		printf("Woody Woodpecker informs you that you need to give him an executable to encrypt ! \n");
	return (0);
}
