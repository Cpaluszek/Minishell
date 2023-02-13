/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_block_redirection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:30:26 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/13 14:11:57 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "structs.h"

void	set_redirection_for_token(t_block *block, t_token *token_list)
{
	t_token *token;

	token = token_list;
	if (block->fd_input != -2)
	{
		while (token)
		{
			if (token->fd_input != NULL )
				token->fd_input = &block->fd_input;
			token = token->next;
		}
	}
	token = token_list;
	if (block->fd_output != -2)
	{
		while (token)
		{
			if (token->fd_output != NULL )
				token->fd_output = &block->fd_output;
			token = token->next;
		}
	}
}

int	open_block_input(t_block *block) // gerer le cas des here_docs
{
	t_token	*token;

	token = block->redirection_token_list;
	if (!token)
		return (0);
	while (token)
	{
		if (token->token <= HERE_DOC)
		{
			if (block->fd_input != -2)
				close(block->fd_input);
			block->fd_input = open(token->str, O_RDONLY);
			if (block->fd_input == -1)
				return (-1);
		}
		token = token->next;
	}
	return (1);
}

void	set_block_fd_input_and_close_unused_fd(t_block *block)
{
	if (block->redirection_status == 1)
	{
		if (block->upper_block && block->upper_block->fd_input != -2)
			close(block->upper_block->fd_input);
		if (block->prev && block->prev->make_a_pipe)
			close(block->prev->pipe_fd[0]);
	}
	else if (block->prev && block->prev->make_a_pipe)
	{
		if (block->upper_block && block->upper_block->fd_input != -2)
			close(block->upper_block->fd_input);
		block->fd_input = block->prev->pipe_fd[0];
	}
	else if (block->upper_block)
		block->fd_input = block->upper_block->fd_input;
}

void	set_block_fd_output_and_close_unused_fd(t_block *block)
{
	if (block->redirection_status == 1)
	{
		if (block->upper_block && block->upper_block->fd_output != -2)
			close(block->upper_block->fd_output);
		if (block->make_a_pipe)
			close(block->pipe_fd[1]);
	}
	else if (block->make_a_pipe)
	{
		if (block->upper_block && block->upper_block->fd_output != -2)
			close(block->upper_block->fd_output);
		block->fd_output = block->pipe_fd[1];
	}
	else if (block->upper_block)
		block->fd_output = block->upper_block->fd_output;
}

int	open_block_output(t_block *block)
{
	t_token	*token;

	token = block->redirection_token_list;
	if (!token)
		return (0);
	while (token)
	{
		if (token->token == OUTPUT_APPEND || token->token == OUTPUT_TRUNC)
		{
			if (block->fd_output != -2)
				close(block->fd_output);
			if (token->token == OUTPUT_TRUNC)
				block->fd_output = open(token->str, O_WRONLY, \
					O_CREAT, O_TRUNC, 0644);
			else
				block->fd_output = open(token->str, O_WRONLY, \
					O_CREAT, O_APPEND, 0644);
			if (block->fd_output == -1)
				return (-1);
		}
		token = token->next;
	}
	return (1);
}
