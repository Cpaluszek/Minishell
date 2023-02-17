/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_in_token_str.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/02/16 18:22:52 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "structs.h"

void		expand_dollar(t_global *shell, t_token *token, char *str);
void		test_failed_malloc(t_global *shell, void *content);
static	int	is_a_heredoc(t_token *token);

// Todo: here_doc delimiter should never be expanded
// Note: expand `~` to $HOME ?
// Note: echo $"HOME" - should primt HOME and not $HOME
void	expand_dollar_in_token_str(t_global *shell)
{
	t_token	*token;

	token = shell->token_list;
	while (token)
	{
		if ((token->token == DQUOTE || token->token == DOLLAR) && \
			ft_is_inside('$', token->str) && is_a_heredoc(token) == 0)
		{
			token->temp_expand = NULL;
			expand_dollar(shell, token, token->str);
			token->str = ft_strjoin_and_free_s2(token->temp_expand, token->str);
			test_failed_malloc(shell, token->str);
			ft_free(token->temp_expand);
		}
		token = token->next;
	}
}

static	int	is_a_heredoc(t_token *token)
{
	while (token && token->token >= CMD &&token->space_link == true)
		token = token->prev;
	if (token && token->token == HERE_DOC)
		return (1);
	return (0);
}
