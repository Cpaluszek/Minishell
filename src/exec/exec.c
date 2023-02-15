/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:00:17 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/15 13:48:12 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "input.h"

// static int	exec_token_list(t_token *token, t_global *shell);
static void	exec_cmd(t_exec *data, t_global *shell);
static int	check_token(t_global *shell, t_token *token, t_exec *data);
static void	check_cmd_exec(t_global *shell, t_exec *data);
static void	close_pipe_fd(t_exec *data);

// Todo: test max amount of pipes
// Todo: test permissions on redirections
// Todo: here_doc always first - process all
// Todo: block execution - all the here_doc needs to be open first
// Attention au close de tout les here_docs en cas de probleme
// void	exec_start(t_global *shell, t_token *token_list)
// {
// 	if (exec_token_list(token_list, shell) == 0)
		
// }
void	print_command_line(t_token *token_list);

int	exec_token_list(t_token *token, t_global *shell)
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
		check_cmd_exec(shell, &data);
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
			perror(ERR_PIPE);
			close_pipe_fd(data);
			exit_shell(shell, EXIT_FAILURE);
		}
		data->pipe = token;
		return (1);
	}
	return (0);
}

static void	check_cmd_exec(t_global *shell, t_exec *data)
{
	t_token	*command;

	command = data->cmd;
	if (command != NULL)
	{
		if (data->prev_pipe)
			command->fd_input = &data->prev_pipe->pipe_fd[0];
		if (data->pipe)
			command->fd_output = &data->pipe->pipe_fd[1];
		exec_cmd(data, shell);
	}
	else
		open_and_immediatly_close_redirection(data->first_token);
	close_pipe_fd(data);
}

static void	exec_cmd(t_exec *data, t_global *shell)
{
	t_token *first_token;
	t_token *command;
	
	command = data->cmd;
	first_token = data->first_token;
	if (check_for_builtins(command, shell))
	{
		close_pipe_fd(data);
		return ;
	}
	command->pid = fork();
	if (command->pid == -1)
	{
		perror(ERR_FORK);
		close_pipe_fd(data);
		exit_shell(shell, EXIT_FAILURE);
	}
	if (command->pid != 0 && ft_strcmp(command->str, "./minishell") == 0)
		signal(SIGINT, SIG_IGN);
	if (command->pid == 0 && exec_child(shell, first_token, command))
	{
		close_pipe_fd(data);
		close_all_file_descriptors(shell->block_fd_list);
		exit(g_status);
	}
}

static void	close_pipe_fd(t_exec *data)
{
	if (data->prev_pipe && close(data->prev_pipe->pipe_fd[0]) == -1)
		perror(ERR_CLOSE);
	if (data->pipe && close(data->pipe->pipe_fd[1]) == -1)
		perror(ERR_CLOSE);
}
