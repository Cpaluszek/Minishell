#########################
#		VARIABLES		#
#########################

# Folders and names
NAME		:= 	libft.a

INC_DIR		:= 	inc/
INC			:= 	libft.h

SRC_DIR		:= 	src/
SRC			:= 	checker/ft_isalpha.c \
 			   	checker/ft_isdigit.c \
 			   	checker/ft_isalnum.c \
 			   	checker/ft_isascii.c \
 			   	checker/ft_isprint.c \
 			   	checker/ft_isspace.c \
 			   	str/ft_toupper.c \
 			   	str/ft_tolower.c \
 			   	str/ft_atoi.c \
 			   	str/ft_strdup.c \
 			   	str/ft_strndup.c \
 			   	str/ft_strchr.c \
 			   	str/ft_strrchr.c \
 			   	str/ft_strlen.c \
 			   	str/ft_strlcpy.c \
 			   	str/ft_strlcat.c \
 			   	str/ft_strcmp.c \
 			   	str/ft_strncmp.c \
 			   	str/ft_strnstr.c \
 			   	str/ft_substr.c \
 			   	str/ft_strjoin.c \
				str/ft_strjoin_and_free.c \
				str/ft_strjoin_and_free_s2.c \
 			   	str/ft_strtrim.c \
 			   	str/ft_split.c \
				str/ft_merge_tab.c \
				str/ft_tab_strdup.c \
				str/ft_size_tab.c \
 			   	str/ft_itoa.c \
 			   	str/ft_strmapi.c \
 			   	str/ft_striteri.c \
				str/ft_is_inside.c \
 			   	mem/ft_calloc.c \
 			   	mem/ft_bzero.c \
 			   	mem/ft_memset.c \
 			   	mem/ft_memcpy.c \
 			   	mem/ft_memmove.c \
 			   	mem/ft_memchr.c \
 			   	mem/ft_memcmp.c \
				mem/ft_free.c \
				mem/ft_free_split.c \
 			   	io/ft_putchar_fd.c \
 			   	io/ft_putstr_fd.c \
 			   	io/ft_putendl_fd.c \
 			   	io/ft_putnbr_fd.c \
				io/ft_printf/ft_printf.c \
				io/ft_printf/ft_pick_conversion_fd.c \
				io/ft_printf/ft_print_decimal_fd.c \
				io/ft_printf/ft_print_hex_fd.c \
				io/ft_printf/ft_print_pointer_fd.c \
				io/ft_printf/ft_print_size_t_base_fd.c \
				io/ft_printf/ft_print_string_fd.c \
				io/ft_printf/ft_print_unsigned_int_fd.c \
				io/ft_printf/ft_printf_fd.c \
				io/gnl/get_next_line.c \
				utils/swap_int.c \
				lst/ft_lstnew.c \
 				lst/ft_lstsize.c \
 			   	lst/ft_lstclear.c \
 			   	lst/ft_lstadd_back.c \
 			   	lst/ft_lstadd_front.c \
 			   	lst/ft_lstlast.c \
 			   	lst/ft_lstdelone.c \
 			   	lst/ft_lstiter.c \
 			   	lst/ft_lstmap.c \
				lst/ft_lstsort.c

OBJ_DIR		:=	build/
OBJ			:=	$(SRC:%.c=$(OBJ_DIR)%.o)

# Compiler options
CC			:=	gcc
DEBUG_FLAG	:= -g3
CC_FLAGS	:=	-Wextra -Werror -Wall $(DEBUG_FLAG)

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

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_DIR)$(INC)
	@mkdir -p $(@D)
	@$(CC) $(CC_FLAGS) -I$(INC_DIR) -c $< -o $@

# clean commands
clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
