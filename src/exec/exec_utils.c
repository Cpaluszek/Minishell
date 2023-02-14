/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:45:52 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/11 10:53:16 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "exec.h"
#include <unistd.h>

void	wait_for_token_list(t_token *token)
{
	while (token)
	{
		if (token->token == CMD)
		{
			if (token->pid > 0 && token->exit_status != COMMAND_NOT_FOUND)
			{
				token->exit_status = 0;
				waitpid(token->pid, &token->exit_status, 0);
				if (WIFEXITED(token->exit_status))
					token->exit_status = WEXITSTATUS(token->exit_status);
				else if (WIFSIGNALED(token->exit_status))
					token->exit_status = WTERMSIG(token->exit_status);
			}
			g_status = token->exit_status;
		}
		token = token->next;
	}
}

void	parent_close_pipes(t_token *token)
{
	if (token->make_a_pipe == 1 && token->pipe_fd[1] > 2 && \
		close(token->pipe_fd[1]) == -1)
		perror(ERR_CLOSE);
	token = token->prev;
	while (token)
	{
		if (token->token == CMD && token->make_a_pipe)
		{
			if (token->pipe_fd[0] > 2 && close(token->pipe_fd[0]) == -1)
				perror(ERR_CLOSE);
			break ;
		}
		token = token->prev;
	}
}

void	close_token_pipes(t_token *token)
{
	if (token->make_a_pipe && close(token->pipe_fd[1]) == -1)
		perror(ERR_CLOSE);
	token = token->prev;
	while (token)
	{
		if (token->token == CMD && token->make_a_pipe)
		{
			if (token->pipe_fd[0] > 2 && close(token->pipe_fd[0]) == -1)
				perror(ERR_CLOSE);
			break ;
		}
		token = token->prev;
	}
}

int	*create_pipe(t_global *shell, t_exec *data, int p_end)
{
	if (pipe(data->cmd->pipe_fd) == -1)
	{
		// close_redirs(data->redirs);
		exec_cmd_error(shell, ERR_PIPE, data->cmd);
	}
	if (p_end)
	{
		data->cmd->fd_output = &data->cmd->pipe_fd[1];
		data->cmd->make_a_pipe = 1;
	}
	else
	{
		data->cmd->fd_input = &data->cmd->pipe_fd[0];
		data->cmd->make_a_pipe = 2;
	}
	return (data->cmd->pipe_fd);
}
