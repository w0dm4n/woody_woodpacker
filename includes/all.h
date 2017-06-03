/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 06:09:59 by frmarinh          #+#    #+#             */
/*   Updated: 2017/05/30 06:10:14 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_H
# define ALL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <sys/mman.h>
# include <string.h>
# include "../libft/includes/libft.h"
# define bool	int
# define true	1
# define false	0

/*
** ELF DEFINITION
*/

# define EI_NIDENT			16			// LENGTH OF DATA
# define MAGIC_LEN			4
# define ELF_MAGIC_HEXA		"7f454c46" // 0x7f E L F (hexa)
# define ARCH_64			2
# define ARCH_32			1
# define L_ENDIAN			1
# define B_ENDIAN			2
# define SHT_SYMTAB			2 // These sections hold a symbol table ; provides symbols for link editing
# define SHT_DYNSYM			11 // These sections hold a symbol table ; olds a minimal set of dynamic linking symbols

/* 64-bit ELF base types. */
typedef unsigned long long			Elf64_Addr;
typedef unsigned short 				Elf64_Half;
typedef signed short 				Elf64_SHalf;
typedef unsigned long long 			Elf64_Off;
typedef signed int 					Elf64_Sword;
typedef unsigned int 				Elf64_Word;
typedef unsigned long long 			Elf64_Xword;
typedef signed long long 			Elf64_Sxword;

typedef struct			elf64_hdr
{
	unsigned char	e_ident[EI_NIDENT];	/* ELF "magic number" */
	Elf64_Half 		e_type;
	Elf64_Half 		e_machine;
	Elf64_Word 		e_version;
	Elf64_Addr 		e_entry;	     /* Entry point virtual address */
	Elf64_Off 		e_phoff;	     /* Program header table file offset */
	Elf64_Off 		e_shoff; 	     /* Section header table file offset */
	Elf64_Word 		e_flags;
	Elf64_Half 		e_ehsize;
	Elf64_Half 		e_phentsize;
	Elf64_Half 		e_phnum;
	Elf64_Half 		e_shentsize;
	Elf64_Half		e_shnum;
	Elf64_Half		e_shstrndx;
}						Elf64_Ehdr;

/*
   sh_size       This member holds the section's size in bytes.  Unless the
                 section type is SHT_NOBITS, the section occupies sh_size
                 bytes in the file.  A section of type SHT_NOBITS may have a
                 nonzero size, but it occupies no space in the file.

   sh_offset     This member's value holds the byte offset from the
                 beginning of the file to the first byte in the section.
                 One section type, SHT_NOBITS, occupies no space in the
                 file, and its sh_offset member locates the conceptual
                 placement in the file.

   e_shnum       This member holds the number of entries in the section
                 header table.  Thus the product of e_shentsize and
                 e_shnum gives the section header table's size in bytes.
                 If a file has no section header table, e_shnum holds the
                 value of zero.

                 If the number of entries in the section header table is
                 larger than or equal to SHN_LORESERVE (0xff00), e_shnum
                 holds the value zero and the real number of entries in
                 the section header table is held in the sh_size member of
                 the initial entry in section header table.  Otherwise,
                 the sh_size member of the initial entry in the section
                 header table holds the value zero.   

   sh_name       This member specifies the name of the section.  Its value
                 is an index into the section header string table section,
                 giving the location of a null-terminated string.
   */

typedef struct			elf64_shdr
{
	Elf64_Word		sh_name;       /* Section name, index in string tbl */
	Elf64_Word		sh_type;       /* Type of section */
	Elf64_Xword		sh_flags;     /* Miscellaneous section attributes */
	Elf64_Addr		sh_addr;       /* Section virtual addr at execution */
	Elf64_Off		sh_offset;      /* Section file offset */
	Elf64_Xword		sh_size;      /* Size of section in bytes */
	Elf64_Word		sh_link;       /* Index of another section */
	Elf64_Word		sh_info;       /* Additional section information */
	Elf64_Xword		sh_addralign; /* Section alignment */
	Elf64_Xword		sh_entsize;   /* Entry size if section holds table */
}						Elf64_Shdr;

typedef struct			s_elf
{
	struct elf64_hdr	*header;
	unsigned char		magic[(MAGIC_LEN * 2) + 1];
	bool				is_64;
	bool				big_endian;
	bool				little_endian;
}						t_elf;

typedef struct	s_data
{
	int			fd;
	off_t		len;
	void		*file_buffer;
	void		*encrypted_buffer;
	t_elf		*elf;
}				t_data;

/*
**	MAIN
*/
void			print_error(char *error, bool should_exit);
void			*ft_mmap(int fd, size_t size);
/*
**	DATA
*/
t_data			*get_data();
/*
**	ELF
*/
void			read_elf(char *file_name);

char			*g_text;
char			*g_bss;
t_data			*g_data;
#endif