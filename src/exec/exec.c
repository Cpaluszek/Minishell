/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:00:17 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/18 19:26:33 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "input.h"

static void	exec_cmd(t_global *shell, t_block *block, t_exec *data);
static int	check_token(t_global *shell, t_token *token, t_exec *data);
static void	check_cmd_exec(t_global *shell, t_block *block, t_exec *data);
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
	close_command_pipe_redirections(data, command);
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
		close_command_pipe_redirections(data, command);
		error_exit_shell(shell, ERR_FORK);
	}
	if (command->pid != 0 && ft_strcmp(command->str, "./minishell") == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	if (command->pid == 0 && exec_child(shell, command, data->pipe, block))
	{
		close_command_pipe_redirections(data, command);
		close_heredocs_file_descriptors(shell->block_fd_list);
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
