/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:41:15 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/01/29 16:02:23 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "token_list_functions.h"
#include <stdio.h>

void	remove_empty_token(t_token *token);
int		syntax_exception(t_token *token1, t_token *token2);
int		print_syntax_error(t_global *shell, char *str);

int	syntax_checking(t_global *shell)
{
	t_token	*token;
	// t_token	*token_list;


	token = shell->token_list;
	// dprintf(1, "BEGIN OF SYNTAX CHECK\n");
	empty_token_assignation(token);
	// token_list = token;
	// while (token_list)
	// {
	// 	dprintf(1, "{ [%d]:[%s]} -> ", token_list->token, token_list->str);
	// 	token_list = token_list->next;
	// }
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
	// dprintf(1, "END OF SYNTAX CHECK --> OK\n");
	return (0);
}

void	empty_token_assignation(t_token *token_list)
{
	t_token	*token;

	token = token_list;
	while (token)
	{
		if (token->token == CMD && not_only_spaces(token->str) == -1)
			token->token = EMPTY;
		token = token->next;
	}
	token = token_list;
	// while (token)
	// {
	// 	if (token->token <= 4 && token->next && token->next->token != EMPTY)
	// 		token->space_link = false;
	// 	else if (token->token == CMD && token->str[0] != ' ')
	// 		token->space_link = false;
	// 	token = token->next;
	// }
	remove_empty_token(token_list);
	// dprintf(1, "OK EMPTY REMOVED\n");
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
			if (token)
				token->prev = temp->prev;
			if (temp->prev)
				temp->prev->next = token;
			ft_lstdelone_token(temp);
		}
		else
			token = token->next;
	}
}

int	syntax_exception(t_token *token1, t_token *token2)
{
	if (token1->token == PIPE && (token2->token <= 3))
	{
		token2->writtable = false;
		return (1);
	}
	if (token1->token == OUTPUT_TRUNC && token2->token == PIPE)
	{
		if (token1->space_link == true)
			return (0);
		remove_token(token2);
		return (1);
	}
	return (0);
}

int	print_syntax_error(t_global *shell, char *str)
{
	ft_printf_fd(2, "%s`%s'\n", ERR_SYNTAX, str);
	shell->command_line = SYNTAX_ERROR;
	add_history(shell->input_completed);
	ft_lstclear_token(&shell->token_list);
	return (1);
}
