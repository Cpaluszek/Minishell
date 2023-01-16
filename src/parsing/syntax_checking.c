/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:41:15 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/01/16 19:16:30 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "token_list_functions.h"

void	empty_token_assignation(t_token *token_list);
void	remove_empty_token(t_token *token);
int		syntax_exception(t_token *token1, t_token *token2);
int		print_syntax_error(t_global *shell, char *str);

int	syntax_checking(t_global *shell)
{
	t_token	*token;

	token = shell->token_list;
	empty_token_assignation(token);
	if (token->token == PIPE)
		return (print_syntax_error(shell, "|"));
	while (token)
	{
		if (token->token <= 4 && token->next && token->next->token <= 4 && \
			!syntax_exception(token, token->next))
			return (print_syntax_error(shell, token->next->token_str));
		else if (token->token <= 3 && !token->next)
			return (print_syntax_error(shell, "newline"));
		token = token->next;
	}
	return (0);
}

void	empty_token_assignation(t_token *token_list)
{
	t_token	*token;
	int		len;

	token = token_list;
	while (token)
	{
		if (token->token == CMD && only_spaces(token->str))
			token->token = EMPTY;
		token = token->next;
	}
	token = token_list;
	while (token)
	{
		len = ft_strlen(token->str);
		if ((token->token <= 4 || token->str[len - 1] != ' ') \
			&& token->next && token->next->token != EMPTY)
			token->space_link = false;
		token = token->next;
	}
	remove_empty_token(token_list);
}

void	remove_empty_token(t_token *token)
{
	t_token	*temp;

	while (token)
	{
		if (token->token == EMPTY)
		{
			temp = token;
			token = token->next;
			token->prev = temp->prev;
			temp->prev->next = token;
			ft_lstdelone_token(temp);
		}
		else
			token = token->next;
	}
}

int	syntax_exception(t_token *token1, t_token *token2)
{
	if (token1->token == PIPE && (token2->token == OUTPUT_TRUNC || \
		token2->token == OUTPUT_APPEND))
	{
		token2->writtable = 0;
		return (1);
	}
	if (token1->token == OUTPUT_TRUNC && token2->token == PIPE)
	{
		if (token1->space_link == true)
			return (0);
		return (1);
	}
	return (0);
}

int	print_syntax_error(t_global *shell, char *str)
{
	ft_printf_fd(2, "%s`%s'\n", ERR_SYNTAX, str);
	add_history(shell->input);
	ft_lstclear_token(shell->token_list);
	ft_free(shell->input);
	return (1);
}
