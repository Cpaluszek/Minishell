/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:45:52 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/08 15:57:05 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "exec.h"
#include "minishell.h"
#include <unistd.h>

void	parent_close_pipes(t_token *token)
{
	if (token->make_a_pipe && token->pipe_fd[1] > 2)
		dprintf(STDERR, " - Parent close 1 [%d] from %s\n", token->pipe_fd[1], token->str);
	if (token->make_a_pipe && token->pipe_fd[1] > 2 && \
		close(token->pipe_fd[1]) == -1)
		perror(ERR_CLOSE);
	if (token->make_a_pipe == 2 && token->pipe_fd[0] > 2 && \
		close(token->pipe_fd[0]) == -1)
		perror(ERR_CLOSE);
	token = token->prev;
	while (token && token->token != PIPE)
	{
		if (token->token == CMD && token->make_a_pipe)
		{
			if (token->pipe_fd[0] > 2 && close(token->pipe_fd[0]) == -1)
				perror(ERR_CLOSE);
			dprintf(STDERR, " - Parent close 0 [%d] from %s\n", token->pipe_fd[0], token->str);
			break ;
		}
		token = token->prev;
	}
}

// Note: will probably need one more parameter for the token list,
// with different blocks
void	exec_cmd_error(t_global *shell, char *err, t_token *token)
{
	perror(err);
	if (ft_strcmp(err, ERR_PIPE) != 0)
		close_token_pipes(token);
	close_all_redirections(shell->token_list);
	exit_shell(shell, EXIT_FAILURE);
}

int	args_number(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	dup_fds(t_token *token)
{
	if (token->fd_input != NULL)
	{
		dprintf(STDERR, "----- child(%s): dup fd_in %p = %d\n", token->str, token->fd_input, *(token->fd_input));
		if (dup2(*(token->fd_input), STDIN) == -1)
		{
			perror(ERR_DUP2);
			if (close(*(token->fd_input)) == -1)
				perror(ERR_CLOSE);
			return (EXIT_FAILURE);
		}
		if (close(*(token->fd_input)) == -1)
			perror(ERR_CLOSE);
	}
	if (token->fd_output != NULL)
	{
		dprintf(STDERR, "----- child(%s): dup fd_out %p = %d\n", token->str, token->fd_output, *(token->fd_output));
		if (dup2(*(token->fd_output), STDOUT) == -1)
		{
			perror(ERR_DUP2);
			if (close(*(token->fd_output)) == -1)
				perror(ERR_CLOSE);
			return (EXIT_FAILURE);
		}
		if (close(*(token->fd_output)) == -1)
			perror(ERR_CLOSE);
	}
	return (0);
}

void	close_token_pipes(t_token *token)
{
	dprintf(STDERR, ">> close token pipes\n");
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
