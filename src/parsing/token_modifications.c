/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_modifications.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:30:33 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/24 20:03:14 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	set_pipe_fd_to_command(t_token *token, int *fd_input, \
int *fd_output);
void		print_command_line(t_token *token_list);

void	transform_quote_token(t_global *shell)
{
	t_token *token;

	token = shell->token_list;
	if (token->token == QUOTE || token->token == DQUOTE)
	{
		token->token = CMD;
		token->token_str = "CMD";
	}
	token = token->next;
	while (token)
	{
		if (token->token == PIPE && token->next && 
			(token->next->token == QUOTE || token->next->token == DQUOTE))
			token->next->token = CMD;
		token = token->next;
	}
}

void	add_info_to_command_token(t_global *shell)
{
	t_token	*token;
	t_token	*temp;
	int		*fd_input;
	int		*fd_output;

	token = shell->token_list;
	print_command_line(token);
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
			printf("1 - token id %s:\n IN : %p OUT : %p\n",token->token_str, fd_input, fd_output);
			temp = temp->next;
		}
		while (token && token->token != CMD)
			token = token->next;
		if (token->token == CMD)
			set_pipe_fd_to_command(token, fd_input, fd_output);
		while (token && token->token != PIPE)
			token = token->next;
		if (token)
			token = token->next;
	}
}

static void	set_pipe_fd_to_command(t_token *token, int *fd_input,
int *fd_output)
{
	t_token	*temp;

	printf("Assignation 1 - token id %s:\n IN : %p OUT : %p\n",token->token_str, fd_input, fd_output);
	if (fd_input)
		token->fd_input = fd_input;
	if (fd_output)
		token->fd_output = fd_output;
	printf("Assignation 2- token id %s:\n IN : %p OUT : %p\n",token->token_str, token->fd_input, token->fd_output);
	temp = token;
	while (temp && temp->token != PIPE)
		temp = temp->next;
	if (temp)
	{
		token->make_a_pipe = true;
		if (!fd_output)
			token->fd_output = &token->pipe_fd[1];
	}
	while (temp && temp->token != CMD)
		temp = temp->next;
	if (temp)
		temp->fd_input = &token->pipe_fd[0];
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
