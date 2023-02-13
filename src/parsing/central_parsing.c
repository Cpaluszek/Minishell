/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   central_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 20:03:00 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/13 16:01:51 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "token_list_functions.h"

static void	parsing_initialization(t_global *shell, char *prompt);
static void	parsing_finalization(t_global *shell);
static int	syntax_checking_and_merging_token(t_global *shell);
static int	uncompleted_line(t_global *shell);

// Note: why return an int - the return value is never read
int	central_parsing(t_global *shell, char *prompt)
{
	parsing_initialization(shell, prompt);
	if (syntax_checking_and_merging_token(shell))
		return (1);
	if (uncompleted_line(shell))
		central_parsing(shell, shell->temp_prompt);
	if (shell->command_line == COMPLETED)
		return (0);
	if (shell->command_line == SYNTAX_ERROR || \
		shell->command_line == AMBIGUOUS_REDIRECT)
		return (1);
	parsing_finalization(shell);
	return (0);
}

static void	parsing_initialization(t_global *shell, char *prompt)
{
	get_input(shell, prompt);
	if (quote_parsing(shell, shell->input_completed) == UNCOMPLETED)
		shell->command_line = UNFINISHED_QUOTE;
	else
		shell->command_line = FINISHED_QUOTE;
	expand_dollar_in_token_str(shell);
	token_parsing(shell);
	remove_empty_token(shell, shell->token_list);
}

static int	syntax_checking_and_merging_token(t_global *shell)
{
	if (syntax_checking(shell))
		return (1);
	find_and_merge_linked_token(shell);
	expand_wildcard(shell);
	empty_token_assignation(shell->token_list);
	if (check_for_ambiguous_redirect(shell->token_list))
	{
		shell->command_line = AMBIGUOUS_REDIRECT;
		add_history(shell->input_completed);
		return (1);
	}
	token_merging(shell);
	if (syntax_checking_end(shell))
		return (1);
	return (0);
}

static void	parsing_finalization(t_global *shell)
{
	t_token	*token;

	empty_token_assignation(shell->token_list);
	remove_empty_token(shell, shell->token_list);
	token = shell->token_list;
	while (token)
	{
		if (token->token == QUOTE || token->token == DQUOTE || \
			token->token == DOLLAR)
			token->token = CMD;
		token = token->next;
	}
	add_path_to_command_token(shell);
	set_fd_for_each_command_token(shell->token_list);
	shell->block_list = block_parsing(shell, NULL, shell->token_list);
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
		if (shell->command_line == UNFINISHED_PARENTHESIS)
			shell->temp_prompt = "subsh > ";
		return (1);
	}
	last_token = ft_lstlast_token(shell->token_list);
	if (last_token->token == PIPE || last_token->token == AND \
		|| last_token->token == OR)
	{
		shell->command_line = UNCOMPLETED;
		shell->temp_prompt = "or > ";
		if (last_token->token == PIPE)
			shell->temp_prompt = "pipe > ";
		else if (last_token->token == AND)
			shell->temp_prompt = "and > ";
		ft_lstclear_token(&shell->token_list);
		return (1);
	}
	return (0);
}
