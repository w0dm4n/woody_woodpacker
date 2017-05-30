# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/23 12:48:21 by frmarinh          #+#    #+#              #
#    Updated: 2017/03/16 15:00:34 by frmarinh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_itoabase_uint.c ft_strlen.c ft_putchar.c ft_putstr.c ft_putnbr.c ft_strdup.c ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_strcmp.c ft_atoi.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strncmp.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_putendl.c ft_putendl_fd.c ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_str_replace.c ft_lstaddend.c ft_strposition.c ft_strdelchar.c ft_lenarray.c ft_set_null.c ft_count_lines.c ft_add_in.c ft_check_fd.c ft_strndup.c ft_charcat.c ft_atoi_base.c ft_strreverse.c ft_strtolower.c

O_FILE = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@gcc -c $(SRCS) $(FLAGS) -I includes/
	@ar rc $(NAME) $(O_FILE)
	@ranlib $(NAME)

clean:
	@rm -rf $(O_FILE)

fclean: clean
	@rm -rf $(NAME)

re:		fclean all
