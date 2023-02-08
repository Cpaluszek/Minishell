#########################
#		VARIABLES		#
#########################

# Folders and names
NAME			:=	minishell

HEADERS_DIR		:=	inc
HEADERS_FILES	:=	minishell.h \
					structs.h \
					errors.h \
					env.h \
					exec.h \
					parsing.h \
					token_list_functions.h \
					input.h

HEADERS			:= $(addprefix $(HEADERS_DIR)/, $(HEADERS_FILES))

SRC_DIR			:=	src

PARSING_DIR		:=	parsing
PARSING_FILES	:=	central_parsing.c \
					quote_parsing.c \
					block_parsing.c \
					empty_token_assignation.c \
					expand_dollar_in_token_str.c \
					expand_functions.c \
					add_path_to_command.c \
					init_and_reset_parsing.c \
					syntax_checking.c \
					token_list_functions.c \
					block_list_functions.c \
					ft_lstnew_token.c \
					token_parsing.c \
					set_fd_for_each_command_token.c \
					merging_str_token.c \
					merge_command.c \
					split_command_token.c \
					utils_parsing.c \
					utils_parsing2.c

EXEC_DIR		:=	exec
EXEC_FILES		:=	exec.c \
					child.c \
					redirections.c \
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

INPUT_DIR		:=	input
INPUT_FILES		:=	signals.c \
					signals_handlers.c \
					here_doc_signals_handlers.c \
					here_doc.c

ENV_DIR			:=	env
ENV_FILES		:=	env_expand.c \
					env_utils.c \
					minimum_env.c

PARSING_SRC		:= $(addprefix $(PARSING_DIR)/, $(PARSING_FILES))
EXEC_SRC		:= $(addprefix $(EXEC_DIR)/, $(EXEC_FILES))
BUILTIN_SRC		:= $(addprefix $(BUILTIN_DIR)/, $(BUILTIN_FILES))
INPUT_SRC		:= $(addprefix $(INPUT_DIR)/, $(INPUT_FILES))
ENV_SRC			:= $(addprefix $(ENV_DIR)/, $(ENV_FILES))

SRC_FILES		:=	main.c \
					utils.c \
					$(EXEC_SRC) \
					$(PARSING_SRC) \
					$(BUILTIN_SRC) \
					$(INPUT_SRC) \
					$(ENV_SRC)

SRCS			:= $(addprefix $(SRC_DIR)/, $(SRC_FILES))

LIB_NAMES		:=	lib/libft
LIBS			=	$(subst lib,-l,$(notdir $(LIB_NAMES)))
LIB_LD			=	$(foreach lib,$(LIB_NAMES),-L$(lib))
LIB_PATHS		=	$(foreach lib,$(LIB_NAMES),$(lib)/$(notdir $(lib)).a)
LIB_HEADERS		=	$(foreach lib,$(LIB_NAMES),-I$(lib)/inc/)

LIBS			+=	-lreadline

BUILD_DIR		:=	build
OBJS			:=	$(SRC_FILES:%.c=$(BUILD_DIR)/%.o)
DEPS			:=	$(SRC_FILES:%.c=$(BUILD_DIR)/%.d)
CCDEFS			:=	NAME=\"$(NAME)\"

# Compiler options
CC				:=	cc
DEBUG_FLAG		:=	-g3 #-fsanitize=address
CC_FLAGS		:=	-Wextra -Werror -Wall $(DEBUG_FLAG)
CC_DEPS_FLAGS	:=	-MP -MMD
CC_DEFS_FLAGS	:=	$(foreach def,$(CCDEFS),-D $(def))

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

all: banner $(NAME)

$(LIB_PATHS): force
	@$(foreach lib, $(LIB_NAMES), \
		@$(MAKE) $(lib); \
	)

$(NAME): $(LIB_PATHS) $(OBJS)
	$(CC) $(CC_FLAGS) $(OBJS) $(LIB_LD) $(LIBS) -o $@ 

-include $(DEPS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(LIB_PATHS)
	@mkdir -p $(@D)
	$(CC) $(CC_FLAGS) $(CC_DEPS_FLAGS) $(CC_DEFS_FLAGS) -I$(HEADERS_DIR) $(LIB_HEADERS) -c $< -o $@

clean: banner
	@$(foreach lib, $(LIB_NAMES), \
		@$(MAKE) $(lib) clean; \
	)
	@rm -rf $(BUILD_DIR)
	@rm -rf $(BUILD_DIR_B)

fclean: clean
	@$(foreach lib, $(LIB_NAMES), \
		@$(MAKE) $(lib) fclean; \
	)
	@rm -rf $(NAME)

re: fclean all

banner:
	@echo ""
	@echo "        _       _ __ _          _ _ "
	@echo "  /\/\ (_)_ __ (_) _\ |__   ___| | |"
	@echo " /    \| | '_ \| \ \| '_ \ / _ \ | |"
	@echo "/ /\/\ \ | | | | |\ \ | | |  __/ | |"
	@echo "\/    \/_|_| |_|_\__/_| |_|\___|_|_|"
	@echo ""

.PHONY: all clean fclean re force banner
