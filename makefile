# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/03 22:08:10 by abrunet           #+#    #+#              #
#    Updated: 2019/05/08 16:38:38 by thflahau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	 	= 	lem-in

####### DIRECTORIES #######
HDR			=	include
LIBDIR		=	libft
SRCDIR 		=	srcs
OBJDIR 		= 	obj
LIBPRINTF	=	ft_printf

###### MAKE VARIABLES #####
STDOUT		=	/dev/fd/1
MODE		=

ifeq '$(MODE)' 'silent'
	STDOUT	=	/dev/null
endif

########## FLAGS ##########
CFLAGS 		= 	-Wall				-Wextra				-Werror			\
				-Wpadded			-Wstack-protector	-std=c99

INC 		= 	-I $(HDR)
CDEBUG		=	-g -O0 -fsanitize=address
COPTI		=	-O3

ifeq '$(MODE)' 'opti'
	CFLAGS	+=	$(COPTI)
else ifeq '$(MODE)' 'debug'
	CFLAGS	+=	$(CDEBUG)
endif

######### SOURCES #########
SRC 		= 	main						parsing						\
				parsing_vertices			memory						\
				errors						parsing_edges				\
				print_hashtable				connection_list				\
				hash						queue						\
				stacks						algorithm					\
				movements					breadth_first_search		\
				graph_manipulation			distribution

SRCS		=	$(addprefix $(SRCDIR), $(SRC))
OBJ 		= 	$(patsubst %, $(OBJDIR)/%.o, $(SRC))

LIBFT 		= 	$(LIBDIR)/libft.a
#PRINTF		= 	$(LIBPRINTF)/libftprintf.a

########## COLORS #########
STD			=	\033[0m
GREEN		=	\033[1;32m
RED			=	\033[1;31m
YELLOW		=	\033[1;33m

########## RULES ##########
all				: $(NAME)

$(NAME)			: $(LIBFT) $(PRINTF) $(OBJ)
	printf "$(YELLOW)%-35s$(STD)" "Building $@... " > $(STDOUT)
	gcc $(CFLAGS) $(LIBFT) $(PRINTF) $(OBJ) -o $@
	echo "$(GREEN)DONE$(STD)" > $(STDOUT)

$(LIBFT)		: $(LIBDIR)/libft.h
	printf "$(YELLOW)%-35s$(STD)" "Building $@... " > $(STDOUT)
	make -C $(LIBDIR)
	echo "$(GREEN)DONE$(STD)" > $(STDOUT)

#$(PRINTF)		: $(LIBPRINTF)/ft_printf.h
#	printf "$(YELLOW)%-35s$(STD)" "Building $@... "
#	make -C $(LIBPRINTF)
#	echo "$(GREEN)DONE$(STD)"

$(OBJDIR)/%.o	: $(SRCDIR)/%.c $(HDR)/*.h
	@mkdir -p $(OBJDIR)
	@echo " > Compiling $<..." > $(STDOUT)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

silent			:
	@make MODE=silent

clean			:
	/bin/rm -rf $(OBJDIR)
	make clean -C $(LIBDIR)
#	make clean -C $(LIBPRINTF)
	echo "$(RED)Object files removed$(STD)" > $(STDOUT)

fclean			: clean
	/bin/rm -rf $(NAME)
	make fclean -C $(LIBDIR)
#	make fclean -C $(LIBPRINTF)
	echo "$(RED)$(NAME) removed$(STD)" > $(STDOUT)

re				: fclean all

.PHONY			: all clean fclean
.SILENT			: $(NAME) $(LIBFT) $(PRINTF) clean fclean
