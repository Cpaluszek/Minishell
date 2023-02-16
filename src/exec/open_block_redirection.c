/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_block_redirection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:30:26 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/16 10:08:18 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "structs.h"

static int	open_block_output(t_block *block, t_token * token);
static void	link_heredoc_to_block(t_block * block, t_token *token);

int	open_block_redirections(t_block *block)
{
	t_token	*token;

	token = block->redirection_token_list;
	if (!token)
		return (0);
	while (token)
	{
		if (token->token == INPUT)
		{
			if (block->fd_input != NULL)
				close(*block->fd_input);
			token->fd_file = open(token->str, O_RDONLY);
			if (token->fd_file == -1)
				return (print_execution_error(token->str));
			block->fd_input = &token->fd_file;
		}
		else if (token->token == HERE_DOC)
			link_heredoc_to_block(block, token);
		else if (token->token == OUTPUT_APPEND || token->token == OUTPUT_TRUNC)
			if (open_block_output(block, token) == -1)
				return (-1);
		token = token->next;
	}
	return (1);
}

static void	link_heredoc_to_block(t_block *block, t_token *token)
{
	if (block->fd_input != NULL)
		close(*block->fd_input);
	block->fd_input = &token->pipe_fd[0];
}

static int	open_block_output(t_block *block, t_token *token)
{
	if (token->token == OUTPUT_APPEND || token->token == OUTPUT_TRUNC)
	{
		if (block->fd_output != NULL)
			close(*block->fd_output);
		if (token->token == OUTPUT_TRUNC)
			token->fd_file = open(token->str, O_WRONLY | \
				O_CREAT | O_TRUNC, 0644);
		else
			token->fd_file = open(token->str, O_WRONLY | \
				O_CREAT | O_APPEND, 0644);
		if (token->fd_file == -1)
			return (print_execution_error(token->str));
		block->fd_output = &token->fd_file;
	}
	return (1);
}

void	set_block_redirections(t_global *shell, t_block *block)
{
	if (block->fd_input != NULL)
		add_fd_to_list(shell, block->fd_input);
	else if (block->prev && block->prev->make_a_pipe)
		block->fd_input = &block->prev->pipe_fd[0];
	else if (block->upper_block && block->upper_block->fd_input)
	{
		block->fd_input = block->upper_block->fd_input;
		block->fd_input_level = block->upper_block->fd_input_level + 1;
	}
	if (block->fd_output != NULL)
		add_fd_to_list(shell, block->fd_output);
	else if (block->make_a_pipe)
		block->fd_output = &block->pipe_fd[1];
	else if (block->upper_block && block->upper_block->fd_output)
	{
		block->fd_output = block->upper_block->fd_output;
		block->fd_output_level = block->upper_block->fd_output_level + 1;
	}
}
