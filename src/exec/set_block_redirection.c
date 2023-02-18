/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_block_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 12:33:52 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/18 15:03:30 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	set_block_fd_input_and_close_unused_fd(t_block *block)
{
	if (block->fd_input != NULL)
	{
		if (block->upper_block && block->upper_block->fd_input != NULL)
			close(*block->upper_block->fd_input);
		if (block->prev && block->prev->make_a_pipe)
			close(block->prev->pipe_fd[0]);
	}
	else if (block->prev && block->prev->make_a_pipe)
	{
		if (block->upper_block && block->upper_block->fd_input != NULL)
			close(*block->upper_block->fd_input);
		block->fd_input = &block->prev->pipe_fd[0];
	}
	else if (block->upper_block)
		block->fd_input = block->upper_block->fd_input;
}

void	set_block_fd_output_and_close_unused_fd(t_block *block)
{
	if (block->fd_output != NULL)
	{
		if (block->upper_block && block->upper_block->fd_output != NULL)
			close(*block->upper_block->fd_output);
		if (block->make_a_pipe)
			close(block->pipe_fd[1]);
	}
	else if (block->make_a_pipe)
	{
		if (block->upper_block && block->upper_block->fd_output != NULL)
			close(*block->upper_block->fd_output);
		block->fd_output = &block->pipe_fd[1];
	}
	else if (block->upper_block)
		block->fd_output = block->upper_block->fd_output;
}

void	close_block_redirection(t_block *block)
{
	if (block->fd_input)
		close(*block->fd_input);
	if (block->fd_output)
		close(*block->fd_output);
}
