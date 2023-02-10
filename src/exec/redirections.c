/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:39:33 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/10 11:07:17 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "input.h"

void	close_redirs(int fd_in, int fd_out)
{
	if (fd_in > 0 && close(fd_in) == -1)
		perror(ERR_CLOSE);
	if (fd_out > 0 && close(fd_out) == -1)
		perror(ERR_CLOSE);
}

void	set_redirection(t_global *shell, t_token *tok, int *fd_in, int *fd_out)
{
	if (tok->token <= HERE_DOC)
	{
		if (*fd_in > 0 && close(*fd_in) == -1)
			perror(ERR_CLOSE);
		if (tok->token == INPUT)
			tok->fd_file = open(tok->str, O_RDONLY);
		else
		{
			if (here_doc(shell, tok) != 0)
				{;} //Todo: error
			tok->fd_file = open(HERE_DOC_TMP, O_RDONLY);
		}
		*fd_in = tok->fd_file;
	}
	else if (tok->token <= OUTPUT_APPEND)
	{
		if (*fd_out > 0 && close(*fd_out) == -1)
			perror(ERR_CLOSE);
		if (tok->token == OUTPUT_TRUNC)
			tok->fd_file = open(tok->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (tok->token == OUTPUT_APPEND)
			tok->fd_file = open(tok->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		*fd_out = tok->fd_file;
	}
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
