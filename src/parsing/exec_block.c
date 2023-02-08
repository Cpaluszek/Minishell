/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:58:02 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/06 18:17:19 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	exec_block(t_global *shell, t_block *block)
{
	while (block)
	{
		if (block->make_a_pipe == true)
			pipe(block->pipe_fd);
		block->pid = fork();
		if (block->pid == 0)
		{
			if (open_block_input(block))
			{
				if (block->upper_block && block->upper_block->fd_input)
					close(block->upper_block->fd_input);
				if (block->prev && block->prev->make_a_pipe)
					close(block->prev->pipe_fd[0]);
			}
			else if (block->prev && block->prev->make_a_pipe)
				if (block->upper_block && block->upper_block->fd_input)
					close(block->upper_block->fd_input);
			if (open_block_output(block))
			{
				if (block->upper_block && block->upper_block->fd_input)
					close(block->upper_block->fd_output);
				if (block->make_a_pipe)
					close(block->pipe_fd[1]);
			}
			else if (block->make_a_pipe)
				if (block->upper_block && block->upper_block->fd_input)
					close(block->upper_block->fd_input);
			if (block->make_a_pipe)
				close(block->pipe_fd[0]);
			if (block->sub_block)
				exec_block(shell, block->sub_block);
			else
				exec_start(block->token_list);
			if (block->make_a_pipe)
				close(block->pipe_fd[1]);
			close_redirections(block);
			exit(EXIT_SUCCESS);
		}
		if (block->logical_link == PIPE_LINK)
		{
			close(block->pipe_fd[1]);
			block = block->next;
		}
		else
		{
			waitpid(block->pid); //pas le bon wait si plusieurs block avec pipe s'enchainent
			block = find_next_block_to_execute(block, block->logical_link);
		}
	}
}
