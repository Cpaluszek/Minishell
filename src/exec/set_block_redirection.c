/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_block_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:03:26 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/23 13:03:26 by cpalusze         ###   ########.fr       */
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

void	set_block_redirection(t_block *block, t_block *upper_block)
{
	if (upper_block)
	{
		block->fd_input = upper_block->fd_input;
		block->fd_output = upper_block->fd_output;
	}
	if (block->prev && block->prev->make_a_pipe == true)
		block->fd_input = &block->prev->pipe_fd[0];
	if (block->make_a_pipe == true)
		block->fd_output = &block->pipe_fd[1];
}

void	close_block_pipe_redirection(t_block *block)
{
	if (block->make_a_pipe == true)
		close(block->pipe_fd[1]);
	if (block->prev && block->prev->make_a_pipe == true)
		close(block->prev->pipe_fd[0]);
}
