/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:58:02 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/18 15:05:33 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "exec.h"
#include "input.h"

static t_block	*find_next_block_to_execute(t_block *block);
static void		exec_block(t_global *shell, t_block *block);
static void		exec_sub_block(t_global *shell, t_block *block);
static void		wait_for_all_piped_block(t_block *block);

void	exec_block_list(t_global *shell, t_block *block)
{
	while (block)
	{
		if (block->make_a_pipe == true)
			pipe(block->pipe_fd);
		exec_block(shell, block);
		if (block->logical_link == PIPE_LINK)
		{
			close(block->pipe_fd[1]);
			set_execution_signals(shell);
			block = block->next;
		}
		else
		{
			wait_for_all_piped_block(block);
			// set_execution_signals(shell); // ou remettre le set_execution_signal : dans le cas suivant : (sub_block) | CMD , CMD n'aura pas eu de signaux reactives;
			block = find_next_block_to_execute(block);
		}
	}
}

// sleep 2 | ((sleep 4 | sleep 3) | sleep 5)

static void	exec_block(t_global *shell, t_block *block)
{
	if (block->sub_block)
	{
		// signal(SIGQUIT, SIG_IGN);
		// signal(SIGINT, SIG_IGN);
		block->pid = fork();
		if (block->pid == 0)
			exec_sub_block(shell, block);
		if (block->prev && block->prev->make_a_pipe == true)
			close(block->prev->pipe_fd[0]);
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

static void	exec_sub_block(t_global *shell, t_block *block)
{
	// set_execution_signals(shell);
	if (block->make_a_pipe)
		close(block->pipe_fd[0]);
	if (expand_environment_variable_and_wildcard(shell, \
		&block->redirection_token_list))
		exit (EXIT_FAILURE);
	if (open_block_redirections(block) == -1)
		exit (EXIT_FAILURE);
	// set_block_redirections(shell, block);
	set_block_fd_input_and_close_unused_fd(block);
	set_block_fd_output_and_close_unused_fd(block);
	exec_block_list(shell, block->sub_block);
	close_block_redirection(block);
	exit(g_status);
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
}
