/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 23:20:20 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/02 17:14:28 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "token_list_functions.h"

static t_block	*create_sub_block(t_global *shell, t_token *first_token, \
	t_token **previous_token, t_block *upper_block);

t_block	*block_parsing(t_global *shell, t_block *upper_block, t_token *first_token)
{
	t_token	*token;
	t_block *first_block;
	t_block	*new_block;
	t_block	*sub_block;

	(void)new_block;
	first_block = NULL;
	first_block = ft_lstnew_block(upper_block, NULL);
	test_failed_malloc(shell, first_block);
	new_block = first_block;
	token = first_token;
	while (token)
	{
		if (token->token == OPEN_PAR)
		{
			new_block = ft_lstnew_block(upper_block, NULL);
			test_failed_malloc(shell, first_block);
			sub_block = create_sub_block(shell, token, &token->prev, upper_block);
			new_block->sub_block = sub_block;
		// add_link(new_block, token->next);
			ft_lstadd_back_block(&first_block, new_block);
		}
		else
		{
			first_token = token;
			while (token && (token->token > CLOSE_PAR || token->token <= PIPE))
				token = token->next;
			new_block = ft_lstnew_block(upper_block, first_token);
			// add_link(new_block, token);
			ft_lstadd_back_block(&first_block, new_block);
		}
	}
	return (first_block);
}

static t_block	*create_sub_block(t_global *shell, t_token *first_token, \
	t_token **previous_token, t_block *upper_block)
{
	t_token	*token;
	t_block	*sub_block;
	int		nb_parenthesis;

	nb_parenthesis = 1;
	token = first_token->next;
	ft_lstdelone_token(token->prev);
	token->prev = NULL;
	while (nb_parenthesis)
	{
		if (token->token == CLOSE_PAR || token->token == OPEN_PAR)
			nb_parenthesis += 8 - token->token;
		token = token->next;
	}
	token->prev->prev->next = NULL;
	ft_lstdelone_token(token->prev);
	sub_block = block_parsing(shell, upper_block, first_token->next);
	test_failed_malloc(shell, sub_block);
	// if (token->token <= OUTPUT_APPEND)
	// 	add_redirection_for_sub_block(sub_block, token, &token);
	ft_lstdelone_token(first_token);
	(*previous_token)->next = token->next;
	return (sub_block);
}

void	add_redirection_for_sub_block(t_block *sub_block, t_token *token, \
t_token **first_token)
{
	int		*fd_input;
	int		*fd_output;

	fd_input = NULL;
	fd_output = NULL;
	while (token && token->token <= OUTPUT_APPEND)
	{
		if (token->token <= HERE_DOC)
			fd_input = &token->fd_file;
		else if (token->token <= OUTPUT_APPEND)
			fd_output = &token->fd_file;
		token = token->next;
	}
	sub_block->fd_input = fd_input;
	sub_block->fd_output = fd_output;
	*first_token = token;
}

void	add_link_between_blocks(t_block *block, t_token *token)
{
	t_token	*last_token_cmd;
	t_token	*first_token_cmd;

	if (token->token == AND)
		block->logical_link = AND_LINK;
	else if (token->token == OR)
		block->logical_link = OR_LINK;
	else if (token->token == PIPE)
	{
		block->logical_link = PIPE_LINK;
		last_token_cmd = ft_lstlast_token(block->token_list);
		while (last_token_cmd->token != CMD)
			last_token_cmd = last_token_cmd->prev;
		block->pipe_fd0 = &last_token_cmd->pipe_fd[0];
	}
	if (block->prev && block->prev->logical_link == PIPE_LINK)
	{
		first_token_cmd = block->token_list;
		while (first_token_cmd->token != CMD)
			first_token_cmd = first_token_cmd->next;
		first_token_cmd->fd_input = block->prev->pipe_fd0;
	}
}
