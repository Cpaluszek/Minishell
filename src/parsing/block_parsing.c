/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:05:35 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/23 13:05:35 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "token_list_functions.h"

static t_token	*create_new_block(t_global *shell, t_block **block_list, \
	t_block *upper_block, t_token *token);

t_block	*block_parsing(t_global *shell, t_block *upper_block, \
	t_token *first_token)
{
	t_token	*token;
	t_block	*block_list;

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
			break ;
		token = token->next;
	}
	if (token && token->prev)
		token->prev->next = NULL;
	new_block = ft_lstnew_block(upper_block, first_token);
	test_failed_malloc(shell, new_block);
	add_link_between_blocks(new_block, token);
	if (token && token->next)
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
	}
}
