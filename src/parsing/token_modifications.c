/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_modifications.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:30:33 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/18 16:19:23 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

static void	set_pipe_fd_to_command(t_token *token, int *fd_input, int *fd_output);
void	print_command_line(t_token *token_list);

void	transform_quote_token(t_global *shell)
{
	t_token *token;
	t_token *token_list;

	token = shell->token_list;
	token_list = token;
	while (token_list)
	{
		dprintf(1, "{ [%d]:[%s]} -> ", token_list->token, token_list->str);
		token_list = token_list->next;
	}
	printf("\n\n");
	token_list = token;
	if (token->token == QUOTE || token->token == DQUOTE)
		token->token = CMD;
	while (token_list)
	{
		dprintf(1, "{ [%d]:[%s]} -> ", token_list->token, token_list->str);
		token_list = token_list->next;
	}
	printf("\n\n");
	token = token->next;
	// while (token)
	// {
	// 	if (token->token == PIPE && token->next && \
	// 		(token->next->token == QUOTE || token->next->token == DQUOTE))
	// 		token->next->token = CMD;
	// 	token = token->next;
	// }
}

void	add_info_to_command_token(t_global *shell)
{
	t_token *token;
	t_token *temp;
	int		*fd_input;
	int		*fd_output;
	int		work_done;

	token = shell->token_list;
	print_command_line(token);
	work_done = 0;
	while (token)
	{
		fd_input = NULL;
		fd_output = NULL;
		temp = token;
		while (temp && temp->token != PIPE && !work_done)
		{
			if (temp->token >= 0 && temp->token <=1)
				fd_input = &temp->fd_file;
			else if (temp->token >= 2 && temp->token <=3)
				fd_output = &temp->fd_file;
			printf("1 - token id %d:\n%p\n",token->token, fd_output);
			temp = temp->next;
		}
		printf("2 - token id %d:\n%p\n",token->token, fd_output);
		work_done = 1;
		if (token->token == CMD)
			set_pipe_fd_to_command(token, fd_input, fd_output);
		if (token->token == PIPE)
			work_done = 0;
		token = token->next;
	}
}

static void	set_pipe_fd_to_command(t_token *token, int *fd_input, int *fd_output)
{
	t_token *temp;
	
	if (fd_input)
		token->fd_input = fd_input;
	if (fd_output)
		token->fd_output = fd_output;
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
	t_token *token;

	token = shell->token_list;
	while (token)
	{
		if (token->token == PIPE)
			remove_token(token);
		token = token->next;
	}
}
