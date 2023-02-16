/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:27:59 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/16 16:57:45 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "token_list_functions.h"

void		expand_dollar(t_global *shell, t_token *token, char *str);
void		test_failed_malloc(t_global *shell, void *content);
void		expand_wildcard(t_global *shell, t_token **head_list);
static int	check_for_ambiguous_redirect(t_token *token);

int	expand_environment_variable_and_wildcard(t_global *shell, \
	t_token **head_of_list)
{	
	expand_environement_variable(shell, head_of_list, *head_of_list);
	find_and_merge_linked_token(*head_of_list);
	expand_wildcard(*head_of_list);
	token_merging(shell, *head_of_list);
	return (check_for_ambiguous_redirect(*head_of_list));
}

void	expand_environement_variable((t_global *shell, \
	t_token **head_of_list, t_token *token))
{
	t_token	*temp;

	while (token)
	{
		if ((token->token == DQUOTE || token->token == DOLLAR) && \
			ft_is_inside('$', token->str))
		{
			expand_dollar_in_token_str(shell, head_of_list, token);
			temp = token;
			insert_token_list(head_of_list, temp, splitted_token_list);
			token = token->next;
			ft_lstdelone_token(temp);
		}
		else
			token = token->next;
	}
}

void	expand_dollar_in_token_str(t_global *shell, \
		t_token **head_of_list, t_token *token)
{
	t_token	*splitted_token_list;
	t_token	*new;

	token->temp_expand = NULL;
	expand_dollar(shell, token, token->str);
	token->str = ft_strjoin_and_free_s2(token->temp_expand, token->str);
	test_failed_malloc(shell, token->str);
	ft_free(token->temp_expand);
	if (token->token == DOLLAR)
	{
		splitted_token_list = create_sub_dollar_list(shell, \
			token, token->str);
		assign_ambiguous_redirect(shell, token, splitted_token_list);
	}
}

static int	check_for_ambiguous_redirect(t_token *token)
{
	while (token)
	{
		if (token->token <= OUTPUT_APPEND && token->next && \
			token->next->token == EMPTY && \
				token->next->origin_token_str)
		{
			ft_printf_fd(2, "%s: %s: ambiguous redirect\n",
				MININAME, token->next->origin_token_str);
			return (1);
		}
		if (token->token <= OUTPUT_APPEND && token->next && \
			token->next->ambiguous_redirect == true)
		{
			ft_printf_fd(2, "%s: %s: ambiguous redirect\n",
				MININAME, token->next->origin_token_str);
			return (1);
		}
		token = token->next;
	}
	return (0);
}
