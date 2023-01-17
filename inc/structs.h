/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:58:01 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/17 13:31:44 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>

enum e_link {
	NO_LINK = 0,
	OR = 1,
	AND = 2
};

enum e_token
{
	INPUT = 0,
	HERE_DOC = 1,
	OUTPUT_TRUNC = 2,
	OUTPUT_APPEND = 3,
	PIPE = 4,
	CMD = 5,
	DQUOTE = 6,
	QUOTE = 7,
	DOLLAR = 8,
	EMPTY = 9,
	NEW_LINE = 10
};

typedef struct s_block {
	enum e_link			link;
	int					exit_status;
	struct s_block		*next;
	struct s_block		*sub_block;
	struct s_block		*upper_block;
	struct s_token		*token_list;
	int					pipe_count;
	int					block_level;
}	t_block;

// Note: is bool allowed ?
typedef struct s_token {
	enum e_token	token;
	struct s_token	*next;
	struct s_token	*prev;
	char			*str;
	char			*token_str;
	bool			space_link;
	bool			redir_use;
	char			**cmd;
	int				fd_in;
	int				fd_out;
	int				exit_status;
}	t_token;

typedef struct s_global{
	t_list	*env_list;
	char	**env;	//malloc (sizeof(char *) * lstsize(env) + 1)
	char	**path;
	t_block	*block_list;
}	t_global;

#endif