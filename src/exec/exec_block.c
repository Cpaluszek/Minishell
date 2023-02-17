/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:58:02 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/16 23:00:10 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "exec.h"

static t_block	*find_next_block_to_execute(t_block *block);
static void		exec_block_child(t_global *shell, t_block *block);
static void		close_block_redirection(t_block *block);

void	exec_block(t_global *shell, t_block *block)
{
	while (block)
	{
		if (block->make_a_pipe == true)
		{
			pipe(block->pipe_fd);
			add_fd_to_list(shell, &block->pipe_fd[0]);
			add_fd_to_list(shell, &block->pipe_fd[1]);
		}
		exec_block_child(shell, block);
		if (block->logical_link == PIPE_LINK)
			block = block->next;
		else
			block = find_next_block_to_execute(block);
	}
}

static void	exec_block_child(t_global *shell, t_block *block)
{
	if (expand_environment_variable_and_wildcard(shell, \
		&block->redirection_token_list))
		return ;
	block->redirection_status = open_block_redirections(block);
	if (block->redirection_status == -1)
		return ;
	set_block_redirections(shell, block);
	if (block->sub_block)
	{
		exec_block(shell, block->sub_block);
		close_block_redirection(block);
	}
	else if (block->token_list)
	{
		if (expand_environment_variable_and_wildcard(shell, \
			&block->token_list))
			return ;
		add_path_to_command_token(shell, block->token_list);
		exec_token_list(shell, block, block->token_list);
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

static void	close_block_redirection(t_block *block)
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
