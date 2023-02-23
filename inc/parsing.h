/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:57:49 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/19 13:57:28 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "structs.h"
# include "errors.h"
# define PROMPT "\001\033[34;5m\002Minishell-1.0 \001\033[0;32m\002>\001\033[0m\002 "
# define PROMPT_ERR "\001\033[34;5m\002Minishell-1.0 \001\033[0;31m\002>\001\033[0m\002 "
# define MININAME 	"msh"

int		central_parsing(t_global *shell, char *prompt);

/*
	--------------- PARSING INITIALIZATION -----------------------
*/

void	set_environment(t_global *shell, char **env);
void	reset_commands(t_global	*shell);
void	token_parsing(t_global *shell);
int		new_token(t_token **token_list, char *str, \
		int len, enum e_token type);
int		quote_parsing(t_global *shell, char *str);
t_token	*create_sub_token_list(t_global *shell, char *str);

/*
	-------------- CHECKING SYNTAX AND MERGING -------------------
*/

int		syntax_checking(t_global *shell);
void	find_and_merge_linked_token(t_global *shell, t_token *head_list);

/*
	-------------- PARSING FINALIZATION --------------------------
*/

int		make_pipe_heredoc(t_global *shell, t_token *token);
int		fill_all_heredocs(t_global *shell);
void	add_fd_to_list(t_global *shell, int *fd);
void	add_link_between_blocks(t_block *block, t_token *token);
void	create_sub_block(t_global *shell, t_block **block_list, \
		t_block *upper_block, t_token **token);
t_block	*block_parsing(t_global *shell, t_block *upper_block, \
		t_token *first_token);

/*
	-------------- PARSING UTILS ---------------------------------
*/

void	empty_token_assignation(t_token *token_list);
void	close_heredocs_file_descriptors(t_list *fd_list);
void	remove_empty_token(t_token **head_list, t_token *token);
char	**get_path(t_global *shell, char **env);
int		not_only_spaces(char *line);
void	get_input(t_global *shell, char *prompt);
void	remove_token(t_token *token);
void	test_failed_malloc(t_global *shell, void *content);
void	insert_token_list(t_token **head_list, t_token *token, \
		t_token *splitted_token_list);

#endif
