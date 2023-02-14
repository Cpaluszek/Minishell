/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:39:33 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/13 13:35:52 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "input.h"

static void	set_new_redir(t_token *token, int redirs[2]);

void	open_and_immediatly_close_redirection(t_token *token)
{
	while (token && token->token != PIPE)
	{
		if (token->token == OUTPUT_TRUNC)
			token->fd_file = open(token->str, O_RDONLY | O_CREAT | O_TRUNC);
		else if (token->token == OUTPUT_APPEND)
			token->fd_file = open(token->str, O_RDONLY | O_CREAT | O_APPEND);
		if (token->token == OUTPUT_APPEND || token->token == OUTPUT_TRUNC)
		{
			if (token->fd_file == -1)
			{
				ft_printf_fd(2, "msh: %s: %s\n", token->str, strerror(errno));
				return ;
			}
			if (close(token->fd_file) == -1)
				perror(ERR_CLOSE);
		}
		token = token->next;
	}
}

/**
 * @brief Set the redirection file descriptor
 * 
 * @param shell 
 * @param tok 
 * @param redirs 
 * @return int 1 in case of here_doc interrupt
 */
int	set_redirection(t_global *shell, t_token *tok, int redirs[2])
{
	if (tok->token == INPUT)
		tok->fd_file = open(tok->str, O_RDONLY);
	else if (tok->token == HERE_DOC)
	{
		if (here_doc(shell, tok) != 0)
		{
			if (close(tok->pipe_fd[0]) == -1)
				perror(ERR_CLOSE);
			tok->pipe_fd[0] = -1;
			return (1);
		}
		tok->fd_file = tok->pipe_fd[0];
	}
	else if (tok->token == OUTPUT_TRUNC)
		tok->fd_file = open(tok->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (tok->token == OUTPUT_APPEND)
		tok->fd_file = open(tok->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	set_new_redir(tok, redirs);
	return (0);
}

static void	set_new_redir(t_token *token, int redirs[2])
{
	if (token->fd_file == -1 && token->token != HERE_DOC)
		perror(token->str);
	if (token->token <= HERE_DOC)
	{
		if (redirs[0] > 0 && close(redirs[0]) == -1)
			perror(ERR_CLOSE);
		redirs[0] = token->fd_file;
	}
	else
	{
		if (redirs[1] > 0 && close(redirs[1]) == -1)
			perror(ERR_CLOSE);
		redirs[1] = token->fd_file;
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
