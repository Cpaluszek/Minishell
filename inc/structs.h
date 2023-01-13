/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:58:01 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/13 17:15:10 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_block {
    e_link              link;
    int                 exit_status;
    struct s_block      *next;
    struct s_block      *sub_block;
    struct s_block      *upper_block;
    struct s_token      *token_list;
    int                 block_level;
}   t_block;

typedef struct s_token {
    e_token         token;
    struct s_token  *next;
    struct s_token  *prev;
    char            *str;
    
    // IF token == CMD
    // Split into char **
    char            **cmd;
    int             exit_status;
}   t_token;

enum e_link {
    NO_LINK = 0,
    OR = 1,         // ||
    AND = 2,        // &&
};

enum e_token 
{
    // EXEC INFOS
    INPUT = 0,
    HERE_DOC = 1,
    OUTPUT_TRUNC = 2,
    OUTPUT_APPEND = 3,
    CMD = 4,
    PIPE = 5,
    // PARSING UTILS
    DQUOTE = 6,
    QUOTE = 7,
    DOLLAR = 8,
};

#endif