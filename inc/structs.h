/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:58:01 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/21 09:19:10 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>
# include <termios.h>
# include "libft.h"

# define SYNTAX_ERROR -1
# define BEGIN 0
# define COMPLETED 1
# define UNCOMPLETED 2
# define FINISHED_QUOTE 3
# define UNFINISHED_QUOTE 4
# define FINISHED_PARENTHESIS 5
# define UNFINISHED_PARENTHESIS 6
# define HERE_DOC_PROBLEM 7

# define STDIN	0
# define STDOUT	1
# define STDERR	2

extern int	g_status;

enum e_link {
	NO_LINK = 0,
	OR_LINK = 1,
	AND_LINK = 2,
	PIPE_LINK = 3
};

enum e_token {
	INPUT = 0,
	HERE_DOC = 1,
	OUTPUT_TRUNC = 2,
	OUTPUT_APPEND = 3,
	PIPE = 4,
	AND = 5,
	OR = 6,
	OPEN_PAR = 7,
	CLOSE_PAR = 9,
	CMD = 10,
	DQUOTE = 11,
	QUOTE = 12,
	DOLLAR = 13,
	EMPTY = 14,
	NEW_LINE = 15
};

typedef struct s_block {
	enum e_link		logical_link;
	int				pid;
	int				exit_status;
	struct s_block	*next;
	struct s_block	*prev;
	struct s_block	*sub_block;
	struct s_block	*upper_block;
	struct s_token	*token_list;
	struct s_token	*redirection_token_list;
	int				block_level;
	int				*fd_input;
	int				*fd_output;
	bool			make_a_pipe;
	int				pipe_fd[2];
}	t_block;

typedef struct s_token {
	enum e_token	token;
	struct s_token	*next;
	struct s_token	*prev;
	char			*str;
	char			**cmd;
	char			*cmd_path;
	char			*token_str;
	char			*origin_token_str;
	char			*temp_expand;
	bool			space_link;
	bool			ambiguous_redirect;
	int				*fd_input;
	int				*fd_output;
	int				pipe_fd[2];
	int				pid;
	int				fd_file;
	int				exit_status;
}	t_token;

typedef struct s_global {
	t_list			*env_list;
	char			**path;
	char			**env;
	char			*input;
	char			*input_completed;
	char			*temp_prompt;
	int				nb_open_parenthesis;
	t_block			*block_list;
	t_token			*token_list;
	t_list			*heredoc_fd_list;
	int				command_line;
	struct termios	saved_attr;
	struct termios	custom_attr;
}	t_global;

#endif
