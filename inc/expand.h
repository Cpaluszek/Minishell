/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:57:49 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/17 16:41:35 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <stdio.h>
# include <unistd.h>
# include "structs.h"
# include "errors.h"

# define MININAME 	"msh"

/*
	---------------------- GENERAL -----------------------
*/

void	insert_token_list(t_token **head_list, t_token *token, \
		t_token *splitted_token_list);
int		new_token(t_token **token_list, char *str, \
		int len, enum e_token type);
void	empty_token_assignation(t_token *token_list);
void	remove_empty_token(t_token **head_list, t_token *token);
void	add_fd_to_list(t_global *shell, int *fd);
void	print_command_line(t_token *token_list);

/*
	----------------- MERGING & SETTING CMD PATH -----------------------
*/

void	add_path_to_command_token(t_global *shell, t_token *token_list);
void	find_and_merge_linked_token(t_global *shell, t_token *head_list);
void	token_merging(t_global *shell, t_token *head_list);

/*
	----------------- EXPAND ENV VARIABLE & WILDCARD --------------------
*/

int		expand_environment_variable_and_wildcard(t_global *shell, \
		t_token **head_of_list);
void	expand_dollar(t_global *shell, t_token *token, char *str);
t_token	*create_sub_dollar_list(t_global *shell, t_token *temp, char *str);
void	setting_space_links_and_checking_parenthesis(t_global *shell, \
		t_token *token);
void	expand_wildcard(t_global *shell, t_token **head_list);
char	*find_matching_filenames(t_global *shell, char *pattern, t_list *file);

/*
	------------------------ ERRORS -----------------------
*/

int		check_for_ambiguous_redirect(t_token *token);
void	assign_ambiguous_redirect(t_global *shell, t_token *token, \
		t_token *expanded_wildcard);
void	test_failed_malloc(t_global *shell, void *content);

#endif
