/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merging_str_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:54:42 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/02/13 16:02:45 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "token_list_functions.h"
#include "libft.h"
#include <stdio.h>

static void	find_and_merge_linked_token(t_global *shell);
static void	merge_linked_token(t_global *shell, t_token *token_list);
static	int check_for_ambiguous_redirect(t_token *token);
static void	merge_redirection(t_global *shell);

int	token_merging(t_global *shell)
{
	// split_dollar_token(shell);
	// dprintf(1,"\nAFTER_SPLITTING");
	// print_command_line(shell->token_list);
	find_and_merge_linked_token(shell);
	empty_token_assignation(shell->token_list);
	if (check_for_ambiguous_redirect(shell->token_list))
		return (1);
	// dprintf(1,"\nBEFORE MERGE REDIRECTION");
	// print_command_line(shell->token_list);
	merge_redirection(shell);
	// dprintf(1,"\nBEFORE MERGE COMMAND");
	// print_command_line(shell->token_list);
	merge_command(shell);
	return (0);
}

static void	find_and_merge_linked_token(t_global *shell)
{
	t_token	*token;

	token = shell->token_list;
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
		remove_token(temp);
		if (space_link == true)
			break ;
	}
	token_list->str = str;
}

static	int	check_for_ambiguous_redirect(t_token *token)
{
	while (token)
	{
		if (token->token <= OUTPUT_APPEND && token->next && \
			token->next->token == EMPTY && \
				token->next->origin_token_str)
		{
			ft_printf_fd(2, "%s: ambiguous redirect\n",
				token->next->origin_token_str);
			return (1);
		}
		if (token->token <= OUTPUT_APPEND && token->next && \
			token->next->token == DOLLAR && \
			ft_is_inside(' ', token->next->str))
		{
			ft_printf_fd(2, "%s: ambiguous redirect\n",
				token->next->origin_token_str);
			return (1);
		}
		token = token->next;
	}
	return (0);
}

static void	merge_redirection(t_global *shell)
{
	t_token	*token;
	t_token	*temp;

	token = shell->token_list;
	while (token)
	{
		if (token->token <= OUTPUT_APPEND && token->next)
		{
			token->str = ft_strdup(token->next->str);
			test_failed_malloc(shell, token->str);
			temp = token->next;
			remove_token(temp);
		}
		token = token->next;
	}
}
