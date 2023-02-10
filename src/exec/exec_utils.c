/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:45:52 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/10 13:31:44 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "exec.h"
#include "minishell.h"
#include <unistd.h>

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
	if (token->make_a_pipe)
		if (close(token->pipe_fd[0]) == -1 || close(token->pipe_fd[1]) == -1)
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

// Note: will probably need one more parameter for the token list,
// with different blocks
// Todo: close all redirs
void	exec_cmd_error(t_global *shell, char *err, t_token *token)
{
	perror(err);
	if (ft_strcmp(err, ERR_PIPE) != 0)
		close_token_pipes(token);
	exit_shell(shell, EXIT_FAILURE);
}

int	*create_pipe(t_global *shell, t_token *cmd, int redirs[2], int p_end)
{
	if (pipe(cmd->pipe_fd) == -1)
	{
		close_redirs(redirs);
		exec_cmd_error(shell, ERR_PIPE, cmd);
	}
	if (p_end)
	{
		cmd->fd_output = &cmd->pipe_fd[1];
		cmd->make_a_pipe = 1;
	}
	else
	{
		cmd->fd_input = &cmd->pipe_fd[0];
		cmd->make_a_pipe = 2;
	}
	return (cmd->pipe_fd);
}
