/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sub_block.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:06:31 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/23 13:23:01 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "token_list_functions.h"

static t_block	*parse_and_create_sub_block(t_global *shell, \
				t_token **first_token, t_block *upper_block);
static void		add_redirection_for_upper_block(t_block *upper_block, \
				t_token *token, t_token **first_token);
static void		set_link_and_redirection_for_upper_block(t_block *upper_block, \
				t_token *token, t_token **first_token);

void	create_sub_block(t_global *shell, t_block **block_list, \
		t_block *upper_block, t_token **first_token)
{
	t_block	*new_block;
	t_block	*sub_block;

	new_block = ft_lstnew_block(upper_block, NULL);
	test_failed_malloc(shell, new_block);
	sub_block = parse_and_create_sub_block(shell, first_token, new_block);
	new_block->sub_block = sub_block;
	ft_lstadd_back_block(block_list, new_block);
}

static t_block	*parse_and_create_sub_block(t_global *shell, \
				t_token **first_token, t_block *upper_block)
{
	t_token	*token;
	t_token	*begin_of_token_list;
	t_block	*first_sub_block;
	int		nb_parenthesis;

	nb_parenthesis = 1;
	token = (*first_token)->next;
	begin_of_token_list = token;
	ft_lstdelone_token(begin_of_token_list->prev);
	begin_of_token_list->prev = NULL;
	while (nb_parenthesis)
	{
		if (token->token == CLOSE_PAR || token->token == OPEN_PAR)
			nb_parenthesis += 8 - token->token;
		if (nb_parenthesis)
			token = token->next;
	}
	token->prev->next = NULL;
	first_sub_block = block_parsing(shell, upper_block, begin_of_token_list);
	set_link_and_redirection_for_upper_block(upper_block, token, first_token);
	test_failed_malloc(shell, first_sub_block);
	return (first_sub_block);
}

static void	set_link_and_redirection_for_upper_block(t_block *upper_block, \
			t_token *token, t_token **first_token)
{
	if (token && token->next)
	{
		token = token->next;
		ft_lstdelone_token(token->prev);
		token->prev = NULL;
	}
	else
	{
		ft_lstdelone_token(token);
		token = NULL;
	}
	add_redirection_for_upper_block(upper_block, token, first_token);
	add_link_between_blocks(upper_block, *first_token);
	token = *first_token;
	if (token && token->next)
	{
		token = token->next;
		ft_lstdelone_token(token->prev);
		token->prev = NULL;
	}
	*first_token = token;
}

static void	add_redirection_for_upper_block(t_block *upper_block, \
	t_token *token, t_token **first_token)
{
	if (token && token->token <= OUTPUT_APPEND)
		upper_block->redirection_token_list = token;
	while (token && (token->token <= OUTPUT_APPEND || token->token >= CMD))
		token = token->next;
	if (token && token->prev)
		token->prev->next = NULL;
	*first_token = token;
}
