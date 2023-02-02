/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   central_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 20:03:00 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/02 15:36:02 by Teiki            ###   ########.fr       */
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
	get_input(shell, prompt);
	if (quote_parsing(shell, shell->input_completed) == UNCOMPLETED)
	{
		ft_lstclear_token(&shell->token_list);
		parsing_initialization(shell, ">");
	}
	else
		token_parsing(shell);
}

static void	parsing_finalization(t_global *shell)
{
	t_token	*token;
	t_token	*token_list;

	token = shell->token_list;
	token_list = token;
	// print_command_line(token);
	expand_variables(shell);
	token_merging(shell);
	//block_syntax_checking(shell)
	add_path_to_command_token(shell);
	//block_parsing(shell);
	set_fd_for_each_command_token(shell->token_list);
	delete_pipe_token(shell);
	// ft_lstadd_back_block(&shell->block_list, ft_lstnew_block(shell->token_list));
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
		ft_lstclear_token(&shell->token_list);
		return (1);
	}
	return (0);
}
