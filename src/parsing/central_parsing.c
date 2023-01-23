/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   central_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 20:03:00 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/23 11:47:28 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "token_list_functions.h"

static void	parsing_initialization(t_global *shell, char *prompt);
static void	parsing_finalization(t_global *shell);
static int	uncompleted_line(t_global *shell);
void		add_fd_just_for_testing(t_token *token);

int	central_parsing(t_global *shell, char *prompt)
{
	if (shell->command_line == SYNTAX_ERROR)
		return (1);
	if (shell->command_line == COMPLETED)
		return (0);
	parsing_initialization(shell, prompt);
	if (syntax_checking(shell))
		return (1);
	if (uncompleted_line(shell))
		central_parsing(shell, ">");
	parsing_finalization(shell);
	return (0);
}

static void	parsing_initialization(t_global *shell, char *prompt)
{
	t_token	*token_list;

	get_input(shell, prompt);
	token_list = quote_parsing(shell->input);
	token_list = token_parsing(token_list);
	ft_lstadd_back_token(&shell->token_list, token_list);
}

static void	parsing_finalization(t_global *shell)
{
	// transform_quote_token(shell);
	token_dollar_expand_and_str_merging(shell);
	add_path_to_command_token(shell);
	add_info_to_command_token(shell);
	delete_pipe_token(shell);
	// add_fd_just_for_testing(shell->token_list);
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

void	add_fd_just_for_testing(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		token->fd_file = i;
		i++;
		token->pipe_fd[0] = i;
		i++;
		token->pipe_fd[1] = i;
		i++;
		token = token->next;
	}
}
