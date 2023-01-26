#########################
#		VARIABLES		#
#########################

# Folders and names
NAME			:=	minishell

HEADERS			:=	inc
HEADERS_FILES	:=	minishell.h

SRC_DIR			:=	src

PARSING_DIR		:=	parsing
PARSING_FILES	:=	central_parsing.c \
					quote_parsing.c \
					add_path_to_command.c \
					init_and_reset_parsing.c \
					syntax_checking.c \
					token_list_functions.c \
					block_list_functions.c \
					token_parsing.c \
					token_modifications.c \
					merging_str_token.c \
					utils_parsing.c

EXEC_DIR		:=	exec
EXEC_FILES		:=	exec.c \
					child.c \
					signals.c \
					signals_handlers.c \
					redirections.c \
					here_doc.c \
					exec_utils.c
					
BUILTIN_DIR		:=	builtins
BUILTIN_FILES	:=	parse_builtins.c \
					cd.c \
					echo.c \
					env.c \
					exit.c \
					export.c \
					builtins_utils.c \
					pwd.c \
					unset.c

ENV_DIR			:=	env
ENV_FILES		:=	env_expand.c \
					env_utils.c

PARSING_SRC		:= $(addprefix $(PARSING_DIR)/, $(PARSING_FILES))
EXEC_SRC		:= $(addprefix $(EXEC_DIR)/, $(EXEC_FILES))
BUILTIN_SRC		:= $(addprefix $(BUILTIN_DIR)/, $(BUILTIN_FILES))
ENV_SRC			:= $(addprefix $(ENV_DIR)/, $(ENV_FILES))

SRC_FILES		:=	main.c \
					utils.c \
					$(EXEC_SRC) \
					$(PARSING_SRC) \
					$(BUILTIN_SRC) \
					$(ENV_SRC)

SRCS			:= $(addprefix $(SRC_DIR)/, $(SRC_FILES))

LIB_NAMES		:=	lib/libft
LIBS			=	$(subst lib,-l,$(notdir $(LIB_NAMES)))
LIB_LD			=	$(foreach lib,$(LIB_NAMES),-L$(lib))
LIB_PATHS		=	$(foreach lib,$(LIB_NAMES),$(lib)/$(notdir $(lib)).a)
LIB_HEADERS		=	$(foreach lib,$(LIB_NAMES),-I$(lib)/inc/)

LIBS			+=	-lreadline
LIB_LD			+=	-L ~/.brew/opt/readline/lib
LIB_HEADERS		+=	-I ~/.brew/opt/readline/include

BUILD_DIR		:=	build
OBJS			:=	$(SRC_FILES:%.c=$(BUILD_DIR)/%.o)

# Compiler options
CC				:=	cc
DEBUG_FLAG		:=	-g3 #-fsanitize=address
CC_FLAGS		:=	-Wextra -Werror -Wall $(DEBUG_FLAG)

MAKE			:=	make -C

# define standard colors
_END			:=	\x1b[0m
_BOLD			:=	\x1b[1m
_UNDER			:=	\x1b[4m
_REV			:=	\x1b[7m
_GREY			:=	\x1b[30m
_RED			:=	\x1b[31m
_GREEN			:=	\x1b[32m
_YELLOW			:=	\x1b[33m
_BLUE			:=	\x1b[34m
_PURPLE			:=	\x1b[35m
_CYAN			:=	\x1b[36m
_WHITE			:=	\x1b[37m

#########################
# 		RULES			#
#########################

all: $(NAME)

$(LIB_PATHS): force
	@$(foreach lib, $(LIB_NAMES), \
		@$(MAKE) $(lib); \
	)

$(NAME): $(LIB_PATHS) $(OBJS)
	@$(CC) $(CC_FLAGS) $(OBJS) $(LIB_LD) $(LIBS) -o $@ 
	@echo "> $(NAME) Done!\n"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(LIB_PATHS) $(HEADERS)/$(HEADERS_FILES)
	@mkdir -p $(@D)
	@echo "$(_GREEN)compiling: $<$(_END)"
	@$(CC) $(CC_FLAGS) -I$(HEADERS) $(LIB_HEADERS) -c $< -o $@

# clean commands
clean:
	@$(foreach lib, $(LIB_NAMES), \
		@$(MAKE) $(lib) clean; \
	)
	@rm -rf $(BUILD_DIR)
	@rm -rf $(BUILD_DIR_B)

fclean: clean
	@$(foreach lib, $(LIB_NAMES), \
		@$(MAKE) $(lib) fclean; \
	)
	@echo "remove $(NAME)"
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re force
