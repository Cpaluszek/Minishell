/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merging_str_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:54:42 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/01/17 20:20:07 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "token_list_functions.h"
#include "libft.h"

void	merge_command(t_global *shell, t_token *token_list);
void	merge_redirection(t_global *shell, t_token *token_list);
void	remove_token(t_token *token);

void	token_dollar_expand_and_str_merging(t_global *shell)
{
	t_token	*token;

	token = shell->token_list;
	while (token)
	{
		if (token->token <= 3)
			merge_redirection(shell, token);
		token = token->next;
	}
	token = shell->token_list;
	while (token)
	{
		if (token->token == CMD)
		{
			merge_command(shell, token);
			token->cmd = ft_split(token->str, ' ');
			if (!token->cmd)
				error_exit_parsing(shell, ERR_MALLOC);
		}
		token = token->next;
	}
}

void	merge_command(t_global *shell, t_token *token_list)
{
	t_token	*token;
	t_token	*temp;
	char	*str;

	str = token_list->str;
	token = token_list->next;
	while (token && token->token != PIPE)
	{
		if (token->token == CMD || token->token == QUOTE || \
			token->token == DQUOTE)
		{
			str = ft_strjoin_and_free(str, token->str);
			if (!str)
				error_exit_parsing(shell, ERR_MALLOC);
			temp = token;
			token = token->next;
			remove_token(temp);
		}
		else
			token = token->next;
	}
	token_list->str = str;
}

void	merge_redirection(t_global *shell, t_token *token_list)
{
	t_token	*token;
	t_token	*temp;
	char	*str;

	str = token_list->str;
	token = token_list->next;
	while (token && token->token > PIPE)
	{
		if (token->token == CMD || token->token == QUOTE || \
			token->token == DQUOTE)
		{
			str = ft_strjoin_and_free(str, token->str);
			if (!str)
				error_exit_parsing(shell, ERR_MALLOC);
		if (token && token->space_link == true) // retravailler ce point ici
			break ;
			temp = token;
			token = token->next;
			remove_token(temp);
		}
	}
	token_list->str = str;
}

void	remove_token(t_token *token)
{
	if (token->prev)
		token->prev->next = token->next;
	if (token->next)
		token->next->prev = token->prev;
	ft_lstdelone_token(token);
}
