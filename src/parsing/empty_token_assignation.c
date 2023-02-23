/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_token_assignation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:05:57 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/23 13:05:57 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "token_list_functions.h"

void	empty_token_assignation(t_token *token_list)
{
	t_token	*token;

	token = token_list;
	while (token)
	{
		if ((token->token == CMD || token->token == DOLLAR) && \
			not_only_spaces(token->str) == -1)
			token->token = EMPTY;
		token = token->next;
	}
}

void	remove_empty_token(t_token **head_list, t_token *token)
{
	t_token	*temp;

	while (token)
	{
		if (token->token == EMPTY && !token->origin_token_str)
		{
			temp = token;
			token = token->next;
			if (token)
				token->prev = temp->prev;
			if (temp->prev)
				temp->prev->next = token;
			if (!temp->prev)
				*head_list = token;
			ft_lstdelone_token(temp);
		}
		else
			token = token->next;
	}
}
