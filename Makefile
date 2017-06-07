# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/20 17:57:50 by frmarinh          #+#    #+#              #
#    Updated: 2017/05/30 10:49:01 by frmarinh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_WOODY	=	woody_woodpacker

NAME		=   woody_woodpacker
NAMEBASE    =   $(shell basename $(NAME))
LENGTHNAME	=	`printf "%s" $(NAMEBASE) | wc -c`
MAX_COLS	=	$$(echo "$$(tput cols)-24-$(LENGTHNAME)"|bc)

CC			=	gcc -ggdb
#FLAGS		=	-Wall -Wextra -Werror
FLAGS		=
FLAGS_O		=	

SRCDIR_WOODY		=	srcs/
OBJDIR_WOODY		=	objs/

INCDIR				=	includes/
LIBFT_DIR			=	libft/
LIBFT_LIB			=	$(LIBFT_DIR)libft.a

SRCBASE_WOODY	=	\
					main.c				\
					data.c				\
					elf.c				\
					copy.c				\
					build.c				\
					update.c
INCS			=	$(addprefix $(INCDIR), $(INCBASE))

SRCS_WOODY			=	$(addprefix $(SRCDIR_WOODY), $(SRCBASE_WOODY))
OBJS_WOODY			=	$(addprefix $(OBJDIR_WOODY), $(SRCBASE_WOODY:.c=.o))

.SILENT:

all:		$(NAME)

$(NAME):
	if test -f $(NAME_WOODY) ; then												\
		echo "make: Nothing to be done for \`all\`.";				        		\
	else																			\
		make WOODY && 																\
		echo "\r\033[38;5;184m👥  AUTHOR(s): \033[0m\033[K" && 						\
		echo "\r\033[38;5;15m`cat auteur | sed s/^/\ \ \ \ -/g`\033[0m\033[K" &&	\
		echo "\033[38;5;44m☑️  ALL    $(NAMEBASE) is done\033[0m\033[K";				\
	fi

$(OBJDIR_WOODY):
	mkdir -p $(OBJDIR_WOODY)
	mkdir -p $(dir $(OBJS_WOODY))

$(OBJDIR_WOODY)%.o : $(SRCDIR_WOODY)%.c | $(OBJDIR_WOODY)
	$(CC) $(FLAGS) -MMD -c $< -o $@											\
		-I $(LIBFT_DIR)$(INCDIR)											\
		-I $(INCDIR)
	printf "\r\033[38;5;11m%s%*.*s\033[0m\033[K"							\
		"⌛  MAKE          wait ..."										\
		$(MAX_COLS) $(MAX_COLS) "($(@))"

fcleanlib:	fclean
	make -C $(LIBFT_DIR) fclean

re:			fclean all

relib:		fclean fcleanlib all

.PHONY:		fclean fcleanlib clean re relib

WOODY: $(OBJDIR_WOODY) $(OBJS_WOODY)
	make -C $(LIBFT_DIR)
	$(CC) $(FLAGS) $(FLAGS_O) -o $(NAME_WOODY) $(OBJS_WOODY) $(LIBFT_LIB)
	echo "\r\033[38;5;22m📗  MAKE $(NAME_WOODY)"

clean:
	printf "\r\033[38;5;11m⌛  CLEAN  $(NAME_WOODY) pls wait ...\033[0m\033[K"
	if [[ `rm -R $(OBJDIR_WOODY) &> /dev/null 2>&1; echo $$?` == "0" ]]; then	\
		echo "\r\033[38;5;124m📕  CLEAN  $(NAME_WOODY)\033[0m\033[K";			\
	else																	    \
		printf "\r";														    \
	fi

fclean:		clean
	printf "\r\033[38;5;11m⌛  FCLEAN $(NAME_WOODY) pls wait ...\033[0m\033[K"
	if [[ `rm $(NAME_WOODY) &> /dev/null 2>&1; echo $$?` == "0" ]]; then			\
		echo "\r\033[38;5;124m📕  FCLEAN $(NAME_WOODY)\033[0m\033[K";			\
	else																	    \
		printf "\r";														    \
	fi

-include $(OBJS:.o=.d)
