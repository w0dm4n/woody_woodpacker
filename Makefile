# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/20 17:57:50 by frmarinh          #+#    #+#              #
#    Updated: 2017/05/13 21:41:31 by frmarinh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_PING	=	woody_woodpacker

NAME		=   woody_woodpacker
NAMEBASE    =   $(shell basename $(NAME))
LENGTHNAME	=	`printf "%s" $(NAMEBASE) | wc -c`
MAX_COLS	=	$$(echo "$$(tput cols)-24-$(LENGTHNAME)"|bc)

CC			=	gcc -ggdb
FLAGS		=	-Wall -Wextra -Werror
FLAGS_O		=	

SRCDIR_PING		=	srcs/
OBJDIR_PING		=	objs/

INCDIR				=	includes/
LIBFT_DIR			=	libft/
LIBFT_LIB			=	$(LIBFT_DIR)libft.a

SRCBASE_PING	=	\
					main.c                \

INCS			=	$(addprefix $(INCDIR), $(INCBASE))

SRCS_PING			=	$(addprefix $(SRCDIR_PING), $(SRCBASE_PING))
OBJS_PING			=	$(addprefix $(OBJDIR_PING), $(SRCBASE_PING:.c=.o))

.SILENT:

all:		$(NAME)

$(NAME):
	if test -f $(NAME_PING) ; then												\
		echo "make: Nothing to be done for \`all\`.";				        		\
	else																			\
		make ping && 																\
		echo "\r\033[38;5;184m👥  AUTHOR(s): \033[0m\033[K" && 						\
		echo "\r\033[38;5;15m`cat auteur | sed s/^/\ \ \ \ -/g`\033[0m\033[K" &&	\
		echo "\033[38;5;44m☑️  ALL    $(NAMEBASE) is done\033[0m\033[K";				\
	fi

$(OBJDIR_PING):
	mkdir -p $(OBJDIR_PING)
	mkdir -p $(dir $(OBJS_PING))

$(OBJDIR_PING)%.o : $(SRCDIR_PING)%.c | $(OBJDIR_PING)
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

ping: $(OBJDIR_PING) $(OBJS_PING)
	make -C $(LIBFT_DIR)
	$(CC) $(FLAGS) $(FLAGS_O) -o $(NAME_PING) $(OBJS_PING) $(LIBFT_LIB)
	echo "\r\033[38;5;22m📗  MAKE $(NAME_PING)"

clean:
	printf "\r\033[38;5;11m⌛  CLEAN  $(NAME_PING) pls wait ...\033[0m\033[K"
	if [[ `rm -R $(OBJDIR_PING) &> /dev/null 2>&1; echo $$?` == "0" ]]; then	\
		echo "\r\033[38;5;124m📕  CLEAN  $(NAME_PING)\033[0m\033[K";			\
	else																	    \
		printf "\r";														    \
	fi

fclean:		clean
	printf "\r\033[38;5;11m⌛  FCLEAN $(NAME_PING) pls wait ...\033[0m\033[K"
	if [[ `rm $(NAME_PING) &> /dev/null 2>&1; echo $$?` == "0" ]]; then			\
		echo "\r\033[38;5;124m📕  FCLEAN $(NAME_PING)\033[0m\033[K";			\
	else																	    \
		printf "\r";														    \
	fi

-include $(OBJS:.o=.d)