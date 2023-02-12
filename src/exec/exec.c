/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:00:17 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/12 15:46:55 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "input.h"

static int	exec_token_list(t_token *token, t_global *shell);
static void	exec_cmd(t_token *token, t_global *shell, int redirs[2]);
static int	check_token(t_global *shell, t_token *token, t_exec *data);
static void	check_cmd_exec(t_global *shell, t_exec *data);

// Todo: test max amount of pipes
// Todo: test permissions on redirections
// Todo: here_doc always first - process all
// Todo: block execution - all the here_doc needs to be open first
// Attention au close de tout les here_docs en cas de probleme
void	exec_start(t_global *shell)
{
	set_execution_signals(shell);
	if (exec_token_list(shell->token_list, shell) == 0)
		wait_for_token_list(shell->token_list);
}

static int	exec_token_list(t_token *token, t_global *shell)
{
	t_exec	data;

	data.pipe = NULL;
	data.flag = 0;
	while (token)
	{
		data.redirs[0] = 0;
		data.redirs[1] = 0;
		data.cmd = NULL;
		while (token)
		{
			if (token->token <= OUTPUT_APPEND && \
				set_redirection(shell, token, data.redirs) == 1)
				return (close_redirs(data.redirs), 1);
			else if (check_token(shell, token, &data))
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
	if (data->cmd != NULL)
	{
		if (data->flag)
		{
			data->pipe = create_pipe(shell, data, 0);
			if (close(data->cmd->pipe_fd[1]) == -1)
				perror(ERR_CLOSE);
			data->cmd->make_a_pipe = 2;
			data->flag = 0;
		}
		exec_cmd(data->cmd, shell, data->redirs);
	}
	else if (data->pipe && data->pipe[0] > 2 && close(data->pipe[0]) == -1)
		perror(ERR_CLOSE);
	close_redirs(data->redirs);
}

// Todo: too much fork - bash does not exit
static void	exec_cmd(t_token *token, t_global *shell, int redirs[2])
{
	if (redirs[0] != 0)
		token->fd_input = &redirs[0];
	if (redirs[1] != 0)
		token->fd_output = &redirs[1];
	if (check_for_builtins(token, shell))
		return ;
	else if (access(token->cmd_path, X_OK) == -1)
	{
		exec_cmd_not_found(token);
		return ;
	}
	token->pid = fork();
	if (token->pid == -1)
	{
		close_redirs(redirs);
		exec_cmd_error(shell, ERR_FORK, token);
	}
	if (token->pid != 0 && ft_strcmp(token->str, "./minishell") == 0)
		signal(SIGINT, SIG_IGN);
	if (token->pid == 0 && exec_child(token, shell->env))
	{
		close_token_pipes(token);
		exit(EXIT_FAILURE);
	}
	parent_close_pipes(token);
}
