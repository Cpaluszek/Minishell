# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/01 13:00:31 by jlitaudo          #+#    #+#              #
#    Updated: 2023/01/15 20:09:41 by Teiki            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#########################
#		VARIABLES		#
#########################

# Folders and names
NAME		:= minishell

HEAD_DIR	:=	inc/
LIST_HEAD	:=	structs.h\
				token_list_functions.h\
				parsing.h\
				minishell.h\

HEAD		:= $(addprefix $(HEAD_DIR), $(LIST_HEAD))

LIST_TOOLS	:=	

TOOLS_DIR	:=	tools/
TOOLS		:=	$(addprefix $(TOOLS_DIR), $(LIST_TOOLS))

LIST_CHECK	:=	

CHECK_DIR	:=	checking/
CHECKING	:=	$(addprefix $(CHECK_DIR), $(LIST_CHECK))

LIST_BONUS	:=	main_bonus.c\

BONUS_DIR	:= bonus/
BONUS		:= $(addprefix $(BONUS_DIR), $(LIST_BONUS))

LIST_SRC	:=	main.c\
				central_parsing.c\
				token_parsing.c\
				quote_parsing.c\
				token_list_functions.c\
				$(CHECKING)\
				$(TOOLS)\

LIST_SRC_B	:=	$(BONUS)\
				$(CHECKING)\
				$(TOOLS)\

SRC_DIR		:=	src/
SRC			:=	$(addprefix $(SRC_DIR), $(LIST_SRC))

LIBX_DIR	:=	Libft/
LIBX		:=	libft.a 

OBJ_DIR		:= obj/
LIST_OBJ 	:= ${LIST_SRC:.c=.o}
OBJ			:= $(addprefix $(OBJ_DIR), $(LIST_OBJ))

LIST_OBJ_B	:= ${LIST_SRC_B:.c=.o}
OBJ_BONUS	:= $(addprefix $(OBJ_DIR), $(LIST_OBJ_B))

# Compiler options
CC 			:= cc
FLAG 		:= -Wall -Wextra -Werror 
FLAG_LIB	:= -I ./Libft/headers -L ./Libft/libft.a
NORM		:= norminette -R -CheckDefine

# define standard colors
_END		:=	\x1b[0m
_BOLD		:=	\x1b[1m
_UNDER		:=	\x1b[4m
_REV		:=	\x1b[7m
_GREY		:=	\x1b[30m
_RED		:=	\x1b[31m
_GREEN		:=	\x1b[32m
_YELLOW		:=	\x1b[33m
_BLUE		:=	\x1b[34m
_PURPLE		:=	\x1b[35m
_CYAN		:=	\x1b[36m
_WHITE		:=	\x1b[37m

#########################
# 		RULES			#
#########################
 
all:		lib ${NAME}

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEAD)
			@mkdir -p $(@D)
			@echo "$(_GREEN)compiling: $<$(_END)"
			@${CC} ${FLAG} -I $(HEAD_DIR) -I ./Libft/headers -c $< -o $@

$(NAME): 	$(LIBX_DIR)$(LIBX) ${OBJ} $(HEAD)
			@echo "$(_BOLD)$(_BLUE)compiling: $@$(_END)"
			@${CC} -o ${NAME} ${OBJ} $(LIBX_DIR)${LIBX} $(FlAG_LIB) #-fsanitize=leaks
			@echo "$(_BOLD)$(_WHITE)$@ SUCCESSFULLY CREATED$(_END)"

$(NAME_B):	$(LIBX_DIR)$(LIBX) ${OBJ_BONUS} $(HEAD)
			@echo "$(_BOLD)$(_BLUE)compiling: $@$(_END)"
			@${CC} -o ${NAME_B} ${OBJ_BONUS} $(LIBX_DIR)${LIBX} $(FlAG_LIB) #-fsanitize=leaks
			@echo "$(_BOLD)$(_WHITE)$(NAME_B) SUCCESSFULLY CREATED$(_END)"

lib:
			@echo "$(_BOLD)$(_PURPLE) Compilation of $(LIBX) begins $(_END)"
			@make -C $(LIBX_DIR)
			@echo

norm:		$(NORM) $(SRC)

clean:
			@rm -rf ${OBJ_DIR}
			@echo "$(_RED)directory $(OBJ_DIR) deleted$(_END)"

fclean: 	clean
			@rm -f ${NAME} $(NAME_B)
			@echo "$(_RED)$(_BOLD)$(NAME) deleted$(_END)"

fcleanall:	clean
			@make fclean -C $(LIBX_DIR)
			@echo
			@rm -f ${NAME} $(NAME_B)
			@echo "$(_RED)$(_BOLD)$(NAME) deleted$(_END)"

re: 		fclean $(NAME)

reall:		fcleanall all

.PHONY:		all clean fclean fcleanall re reall
