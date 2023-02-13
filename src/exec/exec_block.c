/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:58:02 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/13 14:33:29 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "exec.h"

static t_block	*find_next_block_to_execute(t_block *block);
static void		exec_block_child(t_global *shell, t_block *block);
static void		wait_for_all_piped_block(t_block *block);

void	exec_block(t_global *shell, t_block *block)
{
	while (block)
	{
		if (block->make_a_pipe == true)
			pipe(block->pipe_fd);
		block->pid = fork();
		if (block->pid == 0)
			exec_block_child(shell, block);
		if (block->logical_link == PIPE_LINK)
		{
			close(block->pipe_fd[1]);
			block = block->next;
		}
		else
		{
			wait_for_all_piped_block(block);
			block = find_next_block_to_execute(block);
		}
	}
}

static void	exec_block_child(t_global *shell, t_block *block)
{
	if (block->make_a_pipe)
		close(block->pipe_fd[0]);
	block->redirection_status = open_block_input(block);
	if (block->redirection_status != -1)
		block->redirection_status = open_block_output(block);
	if (block->redirection_status == -1)
	{
		g_status = 1;
		exit(g_status);
	}
	set_block_fd_input_and_close_unused_fd(block);
	set_block_fd_output_and_close_unused_fd(block);
	dprintf(1, "fd_in %d, fd_out%d\n", block->fd_input, block->fd_output);
	if (block->token_list)
		set_redirection_for_token(block, block->token_list);
	if (block->sub_block)
		exec_block(shell, block->sub_block);
	else if (block->token_list)
		exec_start(shell, block->token_list);
	if (block->fd_output != -2) // ne pas oublier de closes ces fds dans l'exec de chaque commande
		close(block->fd_input);
	if (block->fd_output != -2)
		close(block->fd_output);
	exit(g_status);
}

static void	wait_for_all_piped_block(t_block *block)
{
	while (block->prev && block->prev->logical_link == PIPE_LINK)
		block = block->prev;
	while (block && block->logical_link == PIPE_LINK)
	{
		waitpid(block->pid, &block->exit_status, 0);
		g_status = block->exit_status;
		block = block->next;
	}
	waitpid(block->pid, &block->exit_status, 0);
	g_status = block->exit_status;
	dprintf(1, "fg_status : %d\n", g_status);
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
