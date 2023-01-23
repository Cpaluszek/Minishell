/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:57:49 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/23 17:29:21 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "structs.h"
# include "errors.h"

# define PROMPT		"\033[34mminishell-0.1 \033[32m\033[1m>\033[0m "
# define PROMPT_ERR	"\033[34mminishell-0.1 \033[31m\033[1m>\033[0m "

char	**get_path(t_global *shell, char **env);
int		new_token(t_token **list, char *str, int len, enum e_token type);
int		not_only_spaces(char *line);
int		syntax_checking(t_global *shell);
int		central_parsing(t_global *shell, char *prompt);
t_token	*quote_parsing(char *str);
t_token	*token_parsing(t_token *token_list);
void	get_input(t_global *shell, char *prompt);
void	test_failed_malloc(t_global *shell, void *content);
void	token_dollar_expand_and_str_merging(t_global *shell);
void	transform_quote_token(t_global *shell);
void	set_environment(t_global *shell, char **env);
void	add_path_to_command_token(t_global *shell);
void	add_info_to_command_token(t_global *shell);
void	delete_pipe_token(t_global *shell);
void	reset_commands(t_global	*shell);
void	remove_token(t_token *token);

#endif
