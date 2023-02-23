/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:01:12 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/23 13:19:25 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "input.h"

static void	execute_command( t_global *shell, t_block *block, t_exec *data);
static int	find_command_and_next_pipe(t_global *shell, \
			t_token *token, t_exec *data);
static void	setting_command_execution(t_global *shell, \
			t_block *block, t_exec *data);
static void	close_command_pipe_redirections(t_exec *data, t_token *command);

int	exec_token_list(t_global *shell, t_block *block, t_token *token)
{
	t_exec	data;

	data.pipe = NULL;
	data.prev_pipe = NULL;
	while (token)
	{
		data.cmd = NULL;
		data.first_token = token;
		while (token)
		{
			if (find_command_and_next_pipe(shell, token, &data))
				break ;
			token = token->next;
		}
		if (!token)
			data.pipe = NULL;
		else
			token = token->next;
		setting_command_execution(shell, block, &data);
		data.prev_pipe = data.pipe;
	}
	return (0);
}

static int	find_command_and_next_pipe(t_global *shell, \
			t_token *token, t_exec *data)
{
	if (token->token == CMD)
		data->cmd = token;
	else if (token->token == PIPE)
	{
		if (pipe(token->pipe_fd) == -1)
		{
			if (data->prev_pipe)
				close(data->prev_pipe->pipe_fd[0]);
			error_exit_shell(shell, ERR_PIPE);
		}
		data->pipe = token;
		return (1);
	}
	return (0);
}

static void	setting_command_execution(t_global *shell, \
			t_block *block, t_exec *data)
{
	t_token	*command;

	command = data->cmd;
	if (command != NULL)
	{
		if (data->prev_pipe)
			command->fd_input = &data->prev_pipe->pipe_fd[0];
		if (data->pipe)
			command->fd_output = &data->pipe->pipe_fd[1];
		if (open_command_redirections(command, data->first_token) == -1)
		{
			g_status = EXIT_FAILURE;
			return ;
		}
		set_block_redirection_for_command(block, command);
		execute_command(shell, block, data);
	}
	else
		open_and_immediatly_close_redirection(data->first_token);
	close_command_pipe_redirections(data, command);
}

static void	execute_command( t_global *shell, t_block *block, t_exec *data)
{
	t_token	*command;

	command = data->cmd;
	if (check_for_builtins(command, shell))
		return ;
	command->pid = fork();
	if (command->pid == -1)
	{
		close_command_pipe_redirections(data, command);
		error_exit_shell(shell, ERR_FORK);
	}
	if (command->pid != 0 && ft_strcmp(command->str, shell->name) == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	if (command->pid == 0)
	{
		exec_child(shell, command, data->pipe, block);
		close_command_pipe_redirections(data, command);
		close_heredocs_file_descriptors(shell->heredoc_fd_list);
		close_block_redirection(block);
		exit(g_status);
	}
}

static void	close_command_pipe_redirections(t_exec *data, t_token *command)
{
	(void)command;
	if (data->prev_pipe)
		close(data->prev_pipe->pipe_fd[0]);
	if (data->pipe)
		close(data->pipe->pipe_fd[1]);
}
