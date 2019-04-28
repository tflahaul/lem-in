# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/03 22:08:10 by abrunet           #+#    #+#              #
#    Updated: 2019/04/28 11:44:27 by thflahau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	 	= 	lem-in

HDR			=	include
CFLAGS 		= 	-Wall -Werror -Wextra -Wpadded -g -fsanitize=address
INC 		= 	-I include
LIBFT 		= 	libft/libft.a
#PRINTF		= 	ft_printf/libftprintf.a
SRCDIR 		=	srcs
SRC 		= 	main						parsing						\
				parsing_vertices			memory						\
				errors						parsing_edges				\
				print_hashtable				connection_list				\
				hash						queue						\
				stacks						algorithm_test				\
				movements					breadth_first_search

OBJDIR 		= 	obj
SRCS		=	$(addprefix $(SRCDIR), $(SRC))
OBJ 		= 	$(patsubst %, $(OBJDIR)/%.o, $(SRC))

########## COLOR ##########
STD			=	\033[0m
GREEN		=	\033[1;32m
RED			=	\033[1;31m
YELLOW		=	\033[1;33m
###########################

all				: $(NAME)

$(NAME)			: $(LIBFT) $(PRINTF) $(OBJ)
	printf "$(YELLOW)%-35s$(STD)" "Building $@... "
	gcc $(CFLAGS) $(LIBFT) $(PRINTF) $(OBJ) -o $@
	echo "$(GREEN)DONE$(STD)"

$(LIBFT)		: $(HDR)/libft.h
	printf "$(YELLOW)%-35s$(STD)" "Building $@... "
	make -C libft
	echo "$(GREEN)DONE$(STD)"

#$(PRINTF)		: $(HDR)/ft_printf.h
#	printf "$(YELLOW)%-35s$(STD)" "Building $@... "
#	make -C ft_printf/
#	echo "$(GREEN)DONE$(STD)"

$(OBJDIR)/%.o	: $(SRCDIR)/%.c $(HDR)/*.h
	@mkdir -p $(OBJDIR)
	@echo " > Compiling $<..."
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean			:
	rm -rf $(OBJDIR)
	make -C libft clean
#	make -C ft_printf clean
	echo "$(RED)Object files removed$(STD)"

fclean			: clean
	make -C libft fclean
#	make -C ft_printf fclean
	rm -f $(NAME)
	echo "$(RED)$(NAME) removed"

re: fclean all

.PHONY			: all clean fclean
.SILENT			: $(NAME) $(LIBFT) $(PRINTF) clean fclean
