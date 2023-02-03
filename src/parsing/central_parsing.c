/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   central_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 20:03:00 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/03 18:52:20 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "token_list_functions.h"
#include <stdio.h>

static int	parsing_initialization(t_global *shell, char *prompt);
static int	merge_and_finish_syntax_checking(t_global *shell);
static void	parsing_finalization(t_global *shell);
static int	uncompleted_line(t_global *shell);

int	central_parsing(t_global *shell, char *prompt)
{
	if (parsing_initialization(shell, prompt))
		return (1);
	// print_command_line(shell->token_list);
	if (!shell->token_list || syntax_checking(shell))
		return (1);
	if (merge_and_finish_syntax_checking(shell))
		return (1);
	if (uncompleted_line(shell))
		central_parsing(shell, ">");
	if (shell->command_line == COMPLETED)
		return (0);
	if (shell->command_line == SYNTAX_ERROR || \
		shell->command_line == AMBIGUOUS_REDIRECT)
		return (1);
	parsing_finalization(shell);
	return (0);
}

static int	parsing_initialization(t_global *shell, char *prompt)
{
	get_input(shell, prompt);
	if (quote_parsing(shell, shell->input_completed) == UNCOMPLETED)
		shell->command_line = UNFINISHED_QUOTE;
	else
		shell->command_line = FINISHED_QUOTE;
	// dprintf(1, "AFTER QUOTE PARSING\n");
	// print_command_line(shell->token_list);
	expand_dollar_in_token_str(shell);
	// dprintf(1, "AFTER DOLLAR EXPAND\n");
	// print_command_line(shell->token_list);
	token_parsing(shell);
	remove_empty_token(shell, shell->token_list);
	// dprintf(1, "AFTER TOKEN PARSING AND ENPTYT TOKEN REMOVING\n");
	// print_command_line(shell->token_list);
	return (0);
}

static int	merge_and_finish_syntax_checking(t_global *shell)
{
	if (token_merging(shell))
	{
		shell->command_line = AMBIGUOUS_REDIRECT;
		add_history(shell->input_completed);
		return (1);
	}
	// dprintf(1, "AFTER TOKEN MERGING\n");
	// print_command_line(shell->token_list);
	if (syntax_checking_end(shell))
		return (1);
	return (0);
}

static void	parsing_finalization(t_global *shell)
{
	t_token	*token;

	// dprintf(1, "Parsing FINALIZATION\n");
	// print_command_line(shell->token_list);
	empty_token_assignation(shell->token_list);
	remove_empty_token(shell, shell->token_list);
	token = shell->token_list;
	while (token)
	{
		if (token->token == QUOTE || token->token == DQUOTE)
			token->token = CMD;
		token = token->next;
	}
	add_path_to_command_token(shell);
	//block_parsing(shell);
	set_fd_for_each_command_token(shell->token_list); //(sera fait dans la creation des blocks quand on fera les parentheses)
	// set_block_fd_and_pipe_fd
	delete_pipe_token(shell);
	add_history(shell->input_completed);
	if (shell->token_list)
		shell->command_line = COMPLETED;
}

static int	uncompleted_line(t_global *shell)
{
	t_token	*last_token;

	if (shell->command_line == UNFINISHED_QUOTE || \
		shell->command_line == UNFINISHED_PARENTHESIS)
	{
		ft_lstclear_token(&shell->token_list);
		return (1);
	}
	last_token = ft_lstlast_token(shell->token_list);
	if (last_token->token == PIPE || last_token->token == AND \
		|| last_token->token == OR)
	{
		shell->command_line = UNCOMPLETED;
		ft_lstclear_token(&shell->token_list);
		return (1);
	}
	return (0);
}
