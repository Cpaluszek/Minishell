/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:57:49 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/29 18:23:42 by Teiki            ###   ########.fr       */
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

int		central_parsing(t_global *shell, char *prompt);

/*
	---------------- PARSING INITIALIZATION ---------------------
*/

void	set_environment(t_global *shell, char **env);
void	reset_commands(t_global	*shell);
void	empty_token_assignation(t_token *token_list);
int		syntax_checking(t_global *shell);
void	quote_parsing(t_global *shell, char *str);
t_token	*token_parsing(t_token *token_list);
/*
	---------------- PARSING FINALIZATION ---------------------
*/

void	token_merging(t_global *shell);
void	split_command_token(t_global *shell);
void	merge_command(t_global *shell);
void	add_path_to_command_token(t_global *shell);
void	set_fd_for_each_command_token(t_global *shell);
void	delete_pipe_token(t_global *shell);

/*
	---------------- PARSING UTILS ---------------------
*/

char	**get_path(t_global *shell, char **env);
void	new_token(t_global *shell, char *str, int len, enum e_token type);
int		not_only_spaces(char *line);
void	get_input(t_global *shell, char *prompt);
void	remove_token(t_token *token);
void	print_command_line(t_token *token_list);
void	test_failed_malloc(t_global *shell, void *content);

#endif
