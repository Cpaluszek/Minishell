/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_token_assignation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:01:30 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/03 15:21:06 by Teiki            ###   ########.fr       */
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
		if (token->token >= CMD && not_only_spaces(token->str) == -1)
			token->token = EMPTY;
		token = token->next;
	}
}

void	remove_empty_token(t_global *shell, t_token *token)
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
			if (!temp->prev)
				shell->token_list = token;
			ft_lstdelone_token(temp);
		}
		else
			token = token->next;
	}
}
