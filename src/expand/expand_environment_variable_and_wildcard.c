/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_environment_variable_and_wildcard.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:27:59 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/18 12:47:07 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "token_list_functions.h"

static void	expand_environment_variable(t_global *shell, \
			t_token **head_of_list, t_token *token);
static void	expand_dollar_in_token_str(t_global *shell, t_token *token);
static int	is_a_wildcard_in_token_list(t_token *token);

int	expand_environment_variable_and_wildcard(t_global *shell, \
	t_token **head_of_list)
{	
	if (!(*head_of_list))
		return (0);
	expand_environment_variable(shell, head_of_list, *head_of_list);
	find_and_merge_linked_token(shell, *head_of_list);
	if (is_a_wildcard_in_token_list(*head_of_list))
		expand_wildcard(shell, head_of_list);
	empty_token_assignation(*head_of_list);
	if (check_for_ambiguous_redirect(*head_of_list))
	{
		g_status = EXIT_FAILURE;
		return (1);
	}
	token_merging(shell, *head_of_list);
	remove_empty_token(head_of_list, *head_of_list);
	return (0);
}

static void	expand_environment_variable(t_global *shell, \
		t_token **head_of_list, t_token *token)
{
	t_token	*temp;
	t_token	*splitted_dollar_list;

	while (token)
	{
		if ((token->token == DQUOTE || token->token == DOLLAR) && \
			ft_is_inside('$', token->str))
		{
			expand_dollar_in_token_str(shell, token);
			if (token->token == DOLLAR && token->str[0])
			{
				splitted_dollar_list = create_sub_dollar_list(shell, token, \
				token->str);
				assign_ambiguous_redirect(shell, token, splitted_dollar_list);
				temp = token;
				insert_token_list(head_of_list, temp, splitted_dollar_list);
				token = token->next;
				ft_lstdelone_token(temp);
			}
			else
				token = token->next;
		}
		else
			token = token->next;
	}
}

static void	expand_dollar_in_token_str(t_global *shell, t_token *token)
{
	token->temp_expand = NULL;
	expand_dollar(shell, token, token->str);
	token->str = ft_strjoin_and_free_s2(token->temp_expand, token->str);
	test_failed_malloc(shell, token->str);
	ft_free(token->temp_expand);
}

static int	is_a_wildcard_in_token_list(t_token *token)
{
	while (token)
	{
		if ((token->token == CMD || token->token == DOLLAR) \
			&& ft_is_inside('*', token->str))
			return (1);
		token = token->next;
	}
	return (0);
}
