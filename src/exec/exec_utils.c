/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:45:52 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/01 14:10:00 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include <unistd.h>

//TODO : (2eme if) :Il ne faudrait pas plutot aller chercher le token CMD precedent pour fermer son pipe plutot que directement 
//le token precedent 
void	parent_close_pipes(t_token *token)
{
	if (token->make_a_pipe && close(token->pipe_fd[1]) == -1)
		perror(ERR_CLOSE);
	if (token->prev && token->prev->make_a_pipe)
		if (close(token->prev->pipe_fd[0]) == -1)
			perror(ERR_CLOSE);
}

// Note: will probably need one more parameter for the token list,
// with different blocks
void	exec_cmd_error(t_global *shell, char *err, t_token *token)
{
	perror(err);
	if (err != ERR_PIPE)
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
	if (token->make_a_pipe)
		if (close(token->pipe_fd[0]) == -1 || close(token->pipe_fd[1]) == -1)
			perror(ERR_CLOSE);
	if (token->prev && token->prev->make_a_pipe)
		if (close(token->prev->pipe_fd[0] == -1))
			perror(ERR_CLOSE);
}
