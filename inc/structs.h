/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:58:01 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/16 19:34:59 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>

enum e_link {
    NO_LINK = 0,
    OR_L = 1,         // ||
    AND_L = 2,        // &&
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
    enum e_link			link;
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
	char			*token_str;
	bool			space_link;
    bool            writtable;
    
    // IF token == CMD
    // Split into char **
    char			**cmd;
    int				exit_status;
}t_token;

typedef struct s_global{
	t_list	*env;
	char	**path;
	char	*input;
	t_block	*block_list;
	t_token	*token_list;
	int		last_exit_status;
}t_global;

#endif