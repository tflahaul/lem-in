# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abrunet <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/03 22:08:10 by abrunet           #+#    #+#              #
#    Updated: 2019/03/21 18:32:31 by abrunet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	 	= 	lem_in

HDR			=	includes
CFLAGS 		= 	-Wall -Werror -Wextra -g
INC 		= 	-I includes -I libft/includes -I ft_printf/includes
LIBFT 		= 	libft/libft.a
PRINTF		= 	ft_printf/libftprintf.a
SRCDIR 		=	src
SRC 		= 	main	

OBJDIR 		= 	obj
OBJ 		= 	$(patsubst %, $(OBJDIR)/%.o, $(SRC))

##########COLOR##########
STD = \033[0m
GREEN = \033[1;32m
RED = \033[1;31m
YELLOW = \033[1;33m
#########################

all				: $(NAME)

$(NAME)	: $(LIBFT) $(PRINTF) $(OBJ) 
	printf "$(YELLOW)%-35s$(STD)" "Building $@... "
	gcc $(CFLAGS) $(LIBFT) $(PRINTF) $(OBJ) -o $@
	echo "$(GREEN)DONE$(STD)"

$(LIBFT)		: libft/$(HDR)/libft.h 
	printf "$(YELLOW)%-35s$(STD)" "Building $@... "
	make -C libft
	echo "$(GREEN)DONE$(STD)"

$(PRINTF)		:  ft_printf/$(HDR)/ft_printf.h 	
	printf "$(YELLOW)%-35s$(STD)" "Building $@... "
	make -C ft_printf/
	echo "$(GREEN)DONE$(STD)"

$(OBJDIR)/%.o	: %.c $(HDR)/lem_in.h libft/$(HDR)/libft.h ft_printf/$(HDR)/ft_printf.h
	@mkdir -p $(OBJDIR)
	@echo " > Compiling $<..."
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean			:
	rm -rf $(OBJDIR)
	make -C libft clean
	make -C ft_printf clean
	echo "$(RED)Object files removed$(STD)"

fclean			: clean
	make -C libft fclean
	make -C ft_printf fclean
	rm -f $(NAME)
	echo "$(RED)$(NAME) removed"

re: fclean all

.PHONY			: all clean fclean
.SILENT			: $(NAME) $(LIBFT) $(PRINTF) clean fclean
