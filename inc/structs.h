/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:58:01 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/17 16:31:14 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>
# include "libft.h"

# define SYNTAX_ERROR -1
# define UNCOMPLETED 0
# define COMPLETED 1

enum e_link {
    NO_LINK = 0,
    OR_LINK = 1,         // ||
    AND_LINK = 2,        // &&
};

enum e_token 
{
    // EXEC INFOS
    INPUT = 0,
    HERE_DOC = 1,
    OUTPUT_TRUNC = 2,
    OUTPUT_APPEND = 3,
    PIPE = 4,
	AND = 5,
	OR = 6,
	OPEN_PAR = 7,
	CLOSE_PAR = 8,
    CMD = 9,
    // PARSING UTILS
    DQUOTE = 10,
    QUOTE = 11,
    DOLLAR = 12,
	EMPTY = 13,
	NEW_LINE = 14,
};

typedef struct s_block {
    enum e_link			logical_link;
    int					exit_status;
    struct s_block		*next;
    struct s_block		*sub_block;
    struct s_block		*upper_block;
    struct s_token		*token_list;
    int					block_level;
	int					pipe_count;
}   t_block;

typedef struct s_token {
    enum e_token	token;
    struct s_token	*next;
    struct s_token	*prev;
    char			*str;
    char			**cmd;
	char			*token_str;
	bool			space_link;
    bool            redir_use;
	bool			writtable;
	int				fd_input;
	int				fd_output;
    int				exit_status;
}t_token;

typedef struct s_global{
	t_list	*env_list;
	char	**path;
	char	**env;
	char	*input;
	char	*input_completed;
	t_block	*block_list;
	t_token	*token_list;
	int		last_exit_status;
    int		command_line;
}t_global;

#endif