/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:04:49 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/02/23 10:04:52 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "exec.h"
#include "input.h"
#include "minishell.h"

static t_block	*find_next_block_to_execute(t_block *block);
static void		exec_block(t_global *shell, t_block *block);
static void		exec_sub_block(t_global *shell, t_block *block);
static void		wait_for_all_piped_block(t_block *block);

void	exec_block_list(t_global *shell, t_block *block)
{
	while (block)
	{
		if (block->make_a_pipe == true)
			if (pipe(block->pipe_fd) == -1)
				error_exit_shell(shell, ERR_PIPE);
		exec_block(shell, block);
		if (block->logical_link == PIPE_LINK)
			block = block->next;
		else
		{
			wait_for_all_piped_block(block);
			block = find_next_block_to_execute(block);
		}
	}
}

static void	exec_block(t_global *shell, t_block *block)
{
	if (block->sub_block)
	{
		block->pid = fork();
		if (block->pid == -1)
			error_exit_shell(shell, ERR_FORK);
		if (block->pid == 0)
			exec_sub_block(shell, block);
		close_block_pipe_redirection(block);
	}
	else if (block->token_list)
	{
		if (expand_environment_variable_and_wildcard(shell, \
			&block->token_list))
			return ;
		add_path_to_command_token(shell, block->token_list);
		set_block_redirection(block, block->upper_block);
		exec_token_list(shell, block, block->token_list);
		close_block_pipe_redirection(block);
		if (block->logical_link != PIPE_LINK)
			block->exit_status = g_status;
	}
}

static void	exec_sub_block(t_global *shell, t_block *block)
{
	set_sub_block_execution_signals();
	if (block->make_a_pipe)
		close(block->pipe_fd[0]);
	if (expand_environment_variable_and_wildcard(shell, \
		&block->redirection_token_list))
	{
		if (block->make_a_pipe)
			close(block->pipe_fd[1]);
		exit (EXIT_FAILURE);
	}
	if (open_block_redirections(block) == -1)
	{
		if (block->make_a_pipe)
			close(block->pipe_fd[1]);
		exit (EXIT_FAILURE);
	}
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

/**
 * @brief Will go back to the last previous block with 
 * a PIPE_LINK. Then will wait each block.
 */
static void	wait_for_all_piped_block(t_block *block)
{
	while (block->prev && block->prev->logical_link == PIPE_LINK)
		block = block->prev;
	while (block)
	{
		if (block->token_list)
		{
			wait_for_token_list(block->token_list);
			block->exit_status = g_status;
		}
		else
		{
			waitpid(block->pid, &block->exit_status, 0);
			if (WIFEXITED(block->exit_status))
				block->exit_status = WEXITSTATUS(block->exit_status);
			else if (WIFSIGNALED(block->exit_status))
				block->exit_status = 128 + WTERMSIG(block->exit_status);
		}
		g_status = block->exit_status;
		block = block->next;
		if (block && block->prev->logical_link != PIPE_LINK)
			break ;
	}
}
