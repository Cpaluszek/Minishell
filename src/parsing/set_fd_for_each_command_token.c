/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd_for_each_command_token.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:30:33 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/02 14:25:33 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	set_pipe_fd_to_command(t_token *token, int *fd_input, \
int *fd_output);
static void	find_and_set_fd_to_command(t_token **token_id, int *fd_input, \
int *fd_output);
static int	check_command_in_previous_pipe(t_token *token);

void	set_fd_for_each_command_token(t_token *token_list)
{
	t_token	*token;
	t_token	*temp;
	int		*fd_input;
	int		*fd_output;

	token = token_list;
	while (token)
	{
		fd_input = NULL;
		fd_output = NULL;
		temp = token;
		while (temp && temp->token != PIPE)
		{
			if (temp->token >= 0 && temp->token <= 1)
				fd_input = &temp->fd_file;
			else if (temp->token >= 2 && temp->token <= 3)
				fd_output = &temp->fd_file;
			temp = temp->next;
		}
		find_and_set_fd_to_command(&token, fd_input, fd_output);
	}
}

static void	find_and_set_fd_to_command(t_token **token_id, int *fd_input,
int *fd_output)
{
	t_token	*token;

	token = *token_id;
	while (token && token->token != CMD && token->token != PIPE)
		token = token->next;
	if (!token || token->token == PIPE)
	{
		if (token)
			token = token->next;
		*token_id = token;
		return ;
	}
	if (token->token == CMD)
		set_pipe_fd_to_command(token, fd_input, fd_output);
	while (token && token->token != PIPE)
		token = token->next;
	if (token)
		token = token->next;
	*token_id = token;
}

static void	set_pipe_fd_to_command(t_token *token, int *fd_input,
int *fd_output)
{
	t_token	*temp;

	if (fd_input)
		token->fd_input = fd_input;
	if (fd_output)
		token->fd_output = fd_output;
	temp = token->next;
	while (temp && temp->token != CMD)
	{
		if (temp->token == PIPE)
			token->make_a_pipe = true;
		temp = temp->next;
	}
	if (!fd_output && token->make_a_pipe == true)
		token->fd_output = &token->pipe_fd[1];
	if (check_command_in_previous_pipe(token) == 0)
		token->fd_input = &token->pipe_fd[0];
	if (!temp)
	{
		return ;
	}
	temp->fd_input = &token->pipe_fd[0];
}

static int	check_command_in_previous_pipe(t_token *token)
{
	t_token	*first;

	first = token;
	while (first && first->token != PIPE)
		first = first->next;
	if (!first)
		token->make_a_pipe = 2;
	while (token && token->token != PIPE)
		token = token->prev;
	if (!token)
		return (1);
	token = token->prev;
	while (token && token->token != PIPE)
	{
		if (token->token == CMD)
			return (1);
		token = token->prev;
	}
	return (0);
}

void	delete_pipe_token(t_global *shell)
{
	t_token	*token;
	t_token	*next;

	token = shell->token_list;
	while (token)
	{
		if (token->token == PIPE)
		{
			next = token->next;
			remove_token(token);
			token = next;
		}
		else
			token = token->next;
	}
}
