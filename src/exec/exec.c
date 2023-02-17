/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:00:17 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/17 13:21:48 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "input.h"

static void	exec_cmd(t_global *shell, t_block *block, t_exec *data);
static int	check_token(t_global *shell, t_token *token, t_exec *data);
static void	check_cmd_exec(t_global *shell, t_block *block, t_exec *data);
static void	close_command_redirection(t_exec *data, t_token *command, \
			t_block *block);

int		exec_token_list(t_global *shell, t_block *block, t_token *token)
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
			if (check_token(shell, token, &data))
				break ;
			token = token->next;
		}
		if (!token)
			data.pipe = NULL;
		else
			token = token->next;
		check_cmd_exec(shell, block, &data);
		data.prev_pipe = data.pipe;
	}
	return (0);
}

static int	check_token(t_global *shell, t_token *token, t_exec *data)
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

static void	check_cmd_exec(t_global *shell, t_block *block, t_exec *data)
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
		exec_cmd(shell, block, data);
	}
	else
		open_and_immediatly_close_redirection(data->first_token);
	close_command_redirection(data, command, block);
}

static void	exec_cmd( t_global *shell, t_block *block, t_exec *data)
{
	t_token	*command;

	command = data->cmd;
	if (check_for_builtins(command, shell))
		return ;
	command->pid = fork();
	if (command->pid == -1)
	{
		close_command_redirection(data, command, block);
		error_exit_shell(shell, ERR_FORK);
	}
	if (command->pid != 0 && ft_strcmp(command->str, "./minishell") == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	if (command->pid == 0 && exec_child(shell, command, data->pipe))
	{
		close_command_redirection(data, command, block);
		close_all_file_descriptors(shell->block_fd_list);
		exit(g_status);
	}
}

static void	close_command_redirection(t_exec *data, t_token *command, \
	t_block *block)
{
	if (data->prev_pipe && data->prev_pipe->pipe_fd[0] != -1)
	{
		close(data->prev_pipe->pipe_fd[0]);
		data->prev_pipe->pipe_fd[0] = -1;
	}
	if (data->pipe && data->pipe->pipe_fd[1] != -1)
	{
		close(data->pipe->pipe_fd[1]);
		data->pipe->pipe_fd[1] = -1;
	}
	if (!block || !command)
		return ;
	if (command->fd_input && *command->fd_input != -1 \
		&& block->fd_input && *command->fd_input != *block->fd_input)
	{
		close(*command->fd_input);
		*command->fd_input = -1;
	}
	if (command->fd_output && *command->fd_output != -1 \
		&& block->fd_output && *command->fd_output != *block->fd_output)
	{
		close(*command->fd_output);
		*command->fd_output = -1;
	}
}
