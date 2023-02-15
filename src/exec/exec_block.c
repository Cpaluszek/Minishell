/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:58:02 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/15 19:34:03 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "exec.h"

static t_block	*find_next_block_to_execute(t_block *block);
static void		exec_block_child(t_global *shell, t_block *block);
static void		close_block_redirection(t_block * block);

void	exec_block(t_global *shell, t_block *block)
{
	t_list *tok;
	
	while (block)
	{
		if (block->make_a_pipe == true)
		{
			pipe(block->pipe_fd);
			add_fd_to_list(shell, &block->pipe_fd[0]);
			add_fd_to_list(shell, &block->pipe_fd[1]);
			tok = shell->block_fd_list;
			while (tok)
			{
				// dprintf(1, "adding fd : %d\n", *(int *)tok->content);
				tok = tok->next;
			}
		}
		exec_block_child(shell, block);
		if (block->logical_link == PIPE_LINK)
			block = block->next;
		else
			block = find_next_block_to_execute(block);
	}
	// close_all_file_descriptors(shell->block_fd_list);
}

static void	exec_block_child(t_global *shell, t_block *block)
{
	block->redirection_status = open_block_redirections(block);
	if (block->redirection_status == -1)
		return ;
	set_block_redirections(shell, block);
	if (block->token_list)
		set_redirection_for_token(block, block->token_list);
	if (block->sub_block)
	{
		exec_block(shell, block->sub_block);
		close_block_redirection(block);
	}
	else if (block->token_list)
	{
		exec_token_list(block->token_list, shell);
		wait_for_token_list(block->token_list);
	}
}

static t_block	*find_next_block_to_execute(t_block *block)
{
	if (g_status == 0)
		while (block && block->logical_link != AND_LINK)
			block = block->next;
	else
		while (block && block->logical_link != OR_LINK)
			block = block->next;
	if (block)
		block = block->next;
	return (block);
}

static void	close_block_redirection(t_block * block)
{
	if (block->fd_input && block->fd_input_level == 0)
	{
		if (*block->fd_input != -1 && close(*block->fd_input) == -1)
			perror(ERR_CLOSE);
		else
			*block->fd_input = -1;
	}
	if (block->fd_output && block->fd_output_level == 0)
	{
		if (*block->fd_output != -1 && close(*block->fd_output) == -1)
			perror(ERR_CLOSE);
		else
			*block->fd_output = -1;
	}
}
