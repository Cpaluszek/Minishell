/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 23:20:20 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/01 17:05:00 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "token_list_functions.h"

void	block_parsing(t_global *shell, t_token *first_token)
{
	t_token	*token;
	t_block	*new_block;
	t_block	*sub_block;

	(void)token_list;
	token = shell->token_list;
	while (token)
	{
		if (first_token->token == OPEN_PAR)
			sub_block = create_sub_block(shell, first_token, &token);
		// if token == pipe ensuite --> 
		while (token && (token->token > CLOSE_PAR || token->token <= PIPE))
			token = token->next;
		new_block = create_new_block(shell, first_token, token);
		if (token->prev)
			token->prev->next = NULL;

	}
}

t_block	*create_sub_block(t_global, *shell, t_token *first_token, \
	t_token **previous_token)
{
	t_token	*token;

	token = first_token;
}
