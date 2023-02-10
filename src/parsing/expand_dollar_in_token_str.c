/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_in_token_str.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 08:39:22 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/10 17:56:07 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"

void	expand_dollar(t_global *shell, t_token *token, char *str);
void	test_failed_malloc(t_global *shell, void *content);

// Todo: here_doc delimiter should never be expanded
void	expand_dollar_in_token_str(t_global *shell)
{
	t_token	*token;

	token = shell->token_list;
	while (token)
	{
		if ((token->token == DQUOTE || token->token == DOLLAR) && \
			ft_is_inside('$', token->str))
		{
			token->temp_expand = NULL;
			expand_dollar(shell, token, token->str);
			token->str = ft_strjoin_and_free_s2(token->temp_expand, token->str);
			test_failed_malloc(shell, token->str);
			ft_free(token->temp_expand);
			if (token->token == DOLLAR)
				token->token = EMPTY;
		}
		token = token->next;
	}
	// empty_token_assignation(shell->token_list);
}
