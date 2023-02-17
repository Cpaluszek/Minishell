/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   central_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 20:03:00 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/17 16:26:37 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "token_list_functions.h"

static void	parsing_initialization(t_global *shell, char *prompt);
static void	parsing_finalization(t_global *shell);
static int	uncompleted_line(t_global *shell);

int	central_parsing(t_global *shell, char *prompt)
{
	parsing_initialization(shell, prompt);
	if (syntax_checking(shell))
		return (1);
	if (uncompleted_line(shell))
		central_parsing(shell, shell->temp_prompt);
	if (shell->command_line == COMPLETED)
		return (0);
	if (shell->command_line == SYNTAX_ERROR)
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
	token_parsing(shell);
	remove_empty_token(&shell->token_list, shell->token_list);
}

static void	parsing_finalization(t_global *shell)
{
	add_history(shell->input_completed);
	if (fill_all_heredocs(shell))
		return ;
	shell->block_list = block_parsing(shell, NULL, shell->token_list);
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
