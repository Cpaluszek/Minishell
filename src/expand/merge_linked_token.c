/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_linked_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:04:50 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/23 13:22:19 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

static void	merge_linked_token(t_global *shell, t_token *token_list);

void	find_and_merge_linked_token(t_global *shell, t_token *head_list)
{
	t_token	*token;

	token = head_list;
	while (token)
	{
		if (token->token > CLOSE_PAR && token->space_link == false)
			merge_linked_token(shell, token);
		token = token->next;
	}
}

static void	merge_linked_token(t_global *shell, t_token *token_list)
{
	t_token	*token;
	t_token	*temp;
	char	*str;
	bool	space_link;

	str = token_list->str;
	token = token_list->next;
	while (token && token->token > CLOSE_PAR)
	{
		space_link = token->space_link;
		temp = token;
		token = token->next;
		str = ft_strjoin_and_free(str, temp->str);
		token_list->origin_token_str = ft_strjoin_and_free(\
			token_list->origin_token_str, temp->origin_token_str);
		test_failed_malloc(shell, str);
		if (token_list->ambiguous_redirect == false)
			token_list->ambiguous_redirect = temp->ambiguous_redirect;
		remove_token(temp);
		if (space_link == true)
			break ;
	}
	token_list->str = str;
}
