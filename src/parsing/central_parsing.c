/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   central_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 20:03:00 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/29 18:35:37 by Teiki            ###   ########.fr       */
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
	// dprintf(1, "\nAFTER SYNTAX CHECKING\n");
	// print_command_line(shell->token_list);
	if (uncompleted_line(shell))
		central_parsing(shell, ">");
	// dprintf(1, "\nAFTER LINE COMPLETED\n");
	// print_command_line(shell->token_list);
	if (shell->command_line == COMPLETED)
		return (0);
	if (shell->command_line == SYNTAX_ERROR)
		return (1);
	parsing_finalization(shell);
	return (0);
}

static void	parsing_initialization(t_global *shell, char *prompt)
{
	// t_token	*token_list;

	get_input(shell, prompt);
	quote_parsing(shell, shell->input);
	print_command_line(shell->token_list);
	// token_list = token_parsing(shell, shell->token_list);
	// ft_lstadd_back_token(&shell->token_list, token_list);
	// dprintf(1, "\nAFTER TOKEN PARSING\n");
	// print_command_line(shell->token_list);
}

static void	parsing_finalization(t_global *shell)
{
	t_token *token;
	t_token *token_list;

	token = shell->token_list;
	token_list = token;
	// token_expand_variables(shell);
	token_merging(shell);
	add_path_to_command_token(shell);
	set_fd_for_each_command_token(shell);
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
