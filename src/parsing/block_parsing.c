/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 23:20:20 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/10 11:08:56 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "token_list_functions.h"

//TODO : GARBAGE COLLECTOR pour les fails de mallocs

static t_token	*create_new_block(t_global *shell, t_block **block_list, \
	t_block *upper_block, t_token *token);

t_block	*block_parsing(t_global *shell, t_block *upper_block, t_token *first_token)
{
	t_token	*token;
	t_block *block_list;
	
	block_list = NULL;
	token = first_token;
	while (token)
	{
		if (token->token == OPEN_PAR)
			create_sub_block(shell, &block_list, upper_block, &token);

		else
			token = create_new_block(shell, &block_list, upper_block, token);
	}
	return (block_list);
}

static t_token	*create_new_block(t_global *shell, t_block **block_list, \
	t_block *upper_block, t_token *token)
{
	t_block	*new_block;
	t_token	*first_token;
	
	first_token = token;
	while (token && (token->token > CLOSE_PAR || token->token <= PIPE))
	{
		if (token->next && token->next->token == OPEN_PAR)
			break ; // dans les cas ou une parenthese suit un pipe	
		token = token->next;
	}
	if (token)
		token->prev->next = NULL;
	new_block = ft_lstnew_block(upper_block, first_token);
	test_failed_malloc(shell, new_block);
	// add_link_between_block(new_block, token);
	if (token && token->next) // il y aura toujours un token->next sil y a un token normalement (un token de link ne peut etre seul)
	{
		token = token->next;
		ft_lstdelone_token(token->prev);
		token->prev = NULL;
	}
	ft_lstadd_back_block(block_list, new_block);
	return (token);
}

void	add_link_between_blocks(t_block *block, t_token *token)
{
	if (token && token->token == AND)
		block->logical_link = AND_LINK;
	else if (token && token->token == OR)
		block->logical_link = OR_LINK;
	else if (token && token->token == PIPE)
	{
		block->logical_link = PIPE_LINK;
		block->make_a_pipe = true;
		if (!block->fd_output)
			block->fd_output = &block->pipe_fd[1];
	}
	// if (block->prev && block->prev->logical_link == PIPE_LINK)
	// {
	// 	block->previous_block_pipe_fd0 = &block->prev->pipe_fd[0];
	// 	if (!block->fd_input)
	// 		block->fd_input = block->previous_block_pipe_fd0;
	// }
}
