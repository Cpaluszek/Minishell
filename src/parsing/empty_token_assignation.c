/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_token_assignation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:01:30 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/31 15:16:30 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "token_list_functions.h"

static void	remove_empty_token(t_token *token);

void	empty_token_assignation(t_token *token_list)
{
	t_token	*token;

	token = token_list;
	while (token)
	{
		if (token->token == CMD && not_only_spaces(token->str) == -1)
			token->token = EMPTY;
		token = token->next;
	}
	token = token_list;
	while (token)
	{
		if (token->token <= 4 && token->next && token->next->token != EMPTY)
			token->space_link = false;
		token = token->next;
	}
	remove_empty_token(token_list);
}

static void	remove_empty_token(t_token *token)
{
	t_token	*temp;

	while (token)
	{
		if (token->token == EMPTY)
		{
			temp = token;
			token = token->next;
			if (token)
				token->prev = temp->prev;
			if (temp->prev)
				temp->prev->next = token;
			ft_lstdelone_token(temp);
		}
		else
			token = token->next;
	}
}
