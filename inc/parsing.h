/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:57:49 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/16 19:24:33 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <readline/readline.h>
# include <readline/history.h>
# include "structs.h"

# define PROMPT	"minishell-0.1$ "
# define ERR_SYNTAX "syntax error near unexpected token "
# define ERR_DOLLAR "ambiguous redirect\n"
# define ERR_MALLOC "Error with malloc(3)\n"

int		new_token(t_token **list, char *str, int len, enum e_token type);
int		only_spaces(char *line);
int		syntax_checking(t_global *shell);
t_token *quote_parsing(char *str);
t_token	*token_parsing(t_token *token_list);
void	central_parsing(t_global *shell, char *prompt);
void	get_input(t_global *shell, char *prompt);
void	error_exit_parsing(t_global *shell, char *err_msg);

#endif
