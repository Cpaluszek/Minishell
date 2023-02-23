/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:03:59 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/23 13:19:43 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "input.h"

static int	open_command_outputs(t_token *command, t_token *token);

void	open_and_immediatly_close_redirection(t_token *token)
{
	while (token && token->token != PIPE)
	{
		if (token->token == INPUT)
			token->fd_file = open(token->str, O_RDONLY);
		else if (token->token == OUTPUT_TRUNC)
			token->fd_file = open(token->str, \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (token->token == OUTPUT_APPEND)
			token->fd_file = open(token->str, \
			O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (token->token == OUTPUT_APPEND || token->token == OUTPUT_TRUNC || \
			token->token == INPUT)
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

int	open_command_redirections(t_token *command, t_token *token)
{
	while (token && token->token != PIPE)
	{
		if (token->token == INPUT)
		{
			if (command->fd_input)
				close(*command->fd_input);
			token->fd_file = open(token->str, O_RDONLY);
			if (token->fd_file == -1)
				return (print_execution_error(token->str));
			command->fd_input = &token->fd_file;
		}
		else if (token->token == HERE_DOC)
		{
			if (command->fd_input)
				close(*command->fd_input);
			command->fd_input = &token->pipe_fd[0];
		}
		else if (token->token == OUTPUT_APPEND || token->token == OUTPUT_TRUNC)
			if (open_command_outputs(command, token) == -1)
				return (-1);
		token = token->next;
	}
	return (1);
}

static int	open_command_outputs(t_token *command, t_token *token)
{
	if (command->fd_output)
		close(*command->fd_output);
	if (token->token == OUTPUT_TRUNC)
		token->fd_file = open(token->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		token->fd_file = open(token->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (token->fd_file == -1)
		return (print_execution_error(token->str));
	command->fd_output = &token->fd_file;
	return (1);
}

void	set_block_redirection_for_command(t_block *block, t_token *command)
{
	if (command->fd_input == NULL)
		command->fd_input = block->fd_input;
	if (command->fd_output == NULL)
		command->fd_output = block->fd_output;
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
		if (*token->fd_input != -1 && close(*token->fd_input) == -1)
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
		if (*token->fd_output != -1 && close(*token->fd_output) == -1)
			perror(ERR_CLOSE);
	}
	return (0);
}
