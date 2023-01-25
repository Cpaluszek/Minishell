/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   central_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 20:03:00 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/24 20:22:52 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "token_list_functions.h"
#include <stdio.h>

static void	parsing_initialization(t_global *shell, char *prompt);
static void	parsing_finalization(t_global *shell);
static int	uncompleted_line(t_global *shell);

int	central_parsing(t_global *shell, char *prompt)
{
	parsing_initialization(shell, prompt);
	if (syntax_checking(shell))
		return (1);
	if (uncompleted_line(shell))
		central_parsing(shell, ">");
	if (shell->command_line == COMPLETED)
		return (0);
	if (shell->command_line == SYNTAX_ERROR)
		return (1);
	parsing_finalization(shell);
	return (0);
}

static void	parsing_initialization(t_global *shell, char *prompt)
{
	t_token	*token_list;

	get_input(shell, prompt);
	token_list = quote_parsing(shell->input);
	// dprintf(1, "OK AFTER QUOTE PARSING\n");
	token_list = token_parsing(token_list);
	ft_lstadd_back_token(&shell->token_list, token_list);
}

static void	parsing_finalization(t_global *shell)
{
	transform_quote_token(shell);
	t_token *token;
	t_token *token_list;

	token = shell->token_list;
	token_list = token;
	// printf("\nAfter transformation\n\n");
	// while (token_list)
	// {
	// 	dprintf(1, "{ [%d]:[%s]} -> ", token_list->token, token_list->str);
	// 	token_list = token_list->next;
	// }
	// printf("\n\n");
	token_dollar_expand_and_str_merging(shell);
	// printf("\nAfter expand\n\n");
	// token_list = token;
	// // while (token_list)
	// {
	// 	dprintf(1, "{ [%d]:[%s]} -> ", token_list->token, token_list->str);
	// 	token_list = token_list->next;
	// }
	// printf("\n\n");
	// dprintf(1, "OK expand\n");
	add_path_to_command_token(shell);
	add_info_to_command_token(shell);
	delete_pipe_token(shell);
	ft_lstadd_back_block(&shell->block_list, ft_lstnew_block(shell->token_list));
	add_history(shell->input_completed);
	shell->command_line = COMPLETED;
}

static int	uncompleted_line(t_global *shell)
{
	t_token	*last_token;

	last_token = ft_lstlast_token(shell->token_list);
	if (last_token->token == PIPE || last_token->token == AND \
		|| last_token->token == OR)
	{
		shell->command_line = UNCOMPLETED;
		return (1);
	}
	return (0);
}
