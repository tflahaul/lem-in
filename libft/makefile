# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/10 18:37:35 by thflahau          #+#    #+#              #
#    Updated: 2019/04/13 21:36:09 by abrunet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc

INCLUDE	=	../include/

CFLAGS	=	-Wall -Wextra -Werror -I $(INCLUDE) -c -g

NAME	=	libft.a

SRCS	=	ft_isaligned.c	ft_isblank.c	ft_isdigit.c	ft_isprintable.c \
			ft_memset.c		ft_putchar.c	ft_putnstr.c	ft_putstr_endl.c \
			ft_putstr.c		ft_strnew.c		ft_strlen.c		ft_strnjoinfree.c\
			ft_variadic_memory_freeing.c  ft_word_count.c get_next_line_stdin.c\
			ft_strdup.c		ft_strndup.c	ft_strchr.c		ft_strsub.c

OBJDIR	=	objs/

OBJS	=	$(SRCS:.c=.o)

OBJDIR1	=	$(addprefix $(OBJDIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRCS)
	ar -cq $@ $(OBJS)
	ranlib $@

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.SILENT: all $(NAME) clean fclean 
.phony: $(NAME) clean fclean re
