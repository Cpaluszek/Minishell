/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:00:17 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/14 01:01:55 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "input.h"

static int	exec_token_list(t_token *token, t_global *shell);
static void	exec_cmd(t_token *first_token, t_token *command, t_global *shell);
static int	check_token(t_global *shell, t_token *token, t_exec *data);
static void	check_cmd_exec(t_global *shell, t_exec *data);

// Todo: test max amount of pipes
// Todo: test permissions on redirections
// Todo: here_doc always first - process all
// Todo: block execution - all the here_doc needs to be open first
// Attention au close de tout les here_docs en cas de probleme
void	exec_start(t_global *shell, t_token *token_list)
{
	set_execution_signals(shell);
	if (exec_token_list(token_list, shell) == 0)
		wait_for_token_list(token_list);
}

static int	exec_token_list(t_token *token, t_global *shell)
{
	t_exec	data;

	data.pipe = NULL;
	data.flag = 0;
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
		check_cmd_exec(shell, &data);
		if (token != NULL)
			token = token->next;
	}
	return (0);
}

/**
 * @brief Check for cmd or pipe
 * 
 * @param shell 
 * @param token 
 * @param data 
 * @return int 1 if a pipe is met, 0 otherwise
 */
static int	check_token(t_global *shell, t_token *token, t_exec *data)
{
	if (token->token == CMD)
	{
		data->cmd = token;
		if (data->pipe != NULL)
		{
			data->cmd->fd_input = data->pipe;
			data->pipe = NULL;
		}
	}
	else if (token->token == PIPE)
	{
		if (data->cmd != NULL)
			data->pipe = create_pipe(shell, data, 1);
		else
			data->flag = 1;
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
		if (data->flag)
		{
			data->pipe = create_pipe(shell, data, 0);
			if (close(command->pipe_fd[1]) == -1)
				perror(ERR_CLOSE);
			command->make_a_pipe = 2;
			data->flag = 0;
		}
		exec_cmd(data->first_token, data->cmd, shell);
	}
	else
	{
		open_and_immediatly_close_redirection(data->first_token);
		if (data->pipe && data->pipe[0] > 2 && close(data->pipe[0]) == -1)
			perror(ERR_CLOSE);
	}
		
}

// Todo: too much fork - bash does not exit
static void	exec_cmd(t_token *first_token, t_token *command, t_global *shell)
{
	if (check_for_builtins(command, shell))
		return ;
	command->pid = fork();
	if (command->pid == -1) // a voir ce quil faut faire dans ce cas.
	{
		exec_cmd_error(shell, ERR_FORK, command);
	}
	if (command->pid != 0 && ft_strcmp(command->str, "./minishell") == 0)
		signal(SIGINT, SIG_IGN);
	if (command->pid == 0 && exec_child(first_token, command, shell->env))
	{
		close_token_pipes(command);
		exit(EXIT_FAILURE);
	}
	parent_close_pipes(command);
}
