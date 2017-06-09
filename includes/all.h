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
	Elf64_Half 		e_type;				// Type of file (see ET_* below)
	Elf64_Half 		e_machine;			// Required architecture for this file (see EM_*)
	Elf64_Word 		e_version;			// Must be equal to 1
	Elf64_Addr 		e_entry;	     /* Entry point virtual address */
	Elf64_Off 		e_phoff;	     /* Program header table file offset */
	Elf64_Off 		e_shoff; 	     /* Section header table file offset */
	Elf64_Word 		e_flags;	 	 // Processor-specific flags
	Elf64_Half 		e_ehsize;		 // Size of ELF header, in bytes
	Elf64_Half 		e_phentsize;	 // Size of an entry in the program header table
	Elf64_Half 		e_phnum;      	/* Length OF Program segment header. */
	Elf64_Half 		e_shentsize;	// Size of an entry in the section header table
	Elf64_Half		e_shnum;		// Number of entries in the section header table
	Elf64_Half		e_shstrndx;		// Sect hdr table index of sect name string table
}						Elf64_Ehdr;

/* Program segment header.  */

typedef struct		elf64_phdr
{
	Elf64_Word		p_type;			// Type of segment
	Elf64_Word		p_flags;		// Segment flags
	Elf64_Off		p_offset;		// File offset where segment is located, in bytes
	Elf64_Addr		p_vaddr;		// Virtual address of beginning of segment
	Elf64_Addr		p_paddr;		// Physical addr of beginning of segment (OS-specific)
	Elf64_Xword		p_filesz;		// Num. of bytes in file image of segment (may be zero)
	Elf64_Xword		p_memsz;		// Num. of bytes in mem image of segment (may be zero)
	Elf64_Xword		p_align;		// Segment alignment constraint
}					Elf64_Phdr;

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


typedef struct			s_segment
{
	struct elf64_phdr*	data;
	struct s_segment	*prev;
	struct s_segment	*next;
}						t_segment;

typedef struct			s_section
{
	struct elf64_shdr	*data;
	void				*content;
	struct s_section	*prev;
	struct s_section	*next;
}						t_section;

typedef struct			s_elf
{
	struct elf64_hdr	*header;
	struct s_segment	*segments;
	struct s_section	*sections;
	unsigned char		magic[(MAGIC_LEN * 2) + 1];
	bool				is_64;
	bool				big_endian;
	bool				little_endian;
}
						t_elf;
typedef struct	s_data
{
	int			fd;
	off_t		len;
	int			diff_offset;
	void		*buffer;
	void		*new_buffer;
	int			default_e_shoff;
	int			default_strtab;
	t_elf		*elf;
}				t_data;

typedef struct		s_stub
{
	void	*text;
	int		text_len;
}				t_stub;

/*
**	MAIN
*/
void			print_error(char *error, bool should_exit);
void			*ft_mmap(int fd, size_t size);

/*
**	DATA
*/
t_data			*get_data();
t_section		*get_sections();
t_segment		*get_segments();
void			new_segment(struct elf64_phdr	*segment);
void			new_section(struct elf64_shdr	*section, void *content);

/*
**	ELF
*/
void			read_elf(char *file_name);
void			save_crypted_file(char *file);

/*
**	COPY
*/
void			copy_elf();
void			copy_section(void *ptr, int position, int size);

/*
**	BUILD
*/
void			build();
char			*get_section_name(int offset);

/*
** UPDATE
*/
void			update_elf();

int				g_offset;
t_data			*g_data;
#endif