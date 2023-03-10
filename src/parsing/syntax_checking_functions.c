/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checking_functions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:06:17 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/23 13:23:53 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

int			print_syntax_error(t_global *shell, char *str);
static int	syntax_exception(t_token *token1, t_token *token2);
void		remove_token(t_token *token);

int	token_at_end_of_command_line(t_global *shell, t_token *token)
{
	if (token->token <= OUTPUT_APPEND && !token->next && \
		shell->command_line != UNFINISHED_QUOTE && \
		shell->command_line != UNFINISHED_PARENTHESIS)
		return (print_syntax_error(shell, "newline"));
	return (0);
}

int	two_tokens_in_a_row(t_global *shell, t_token *token1, t_token *token2)
{
	if (token1->token <= CLOSE_PAR && token2 && token2->token \
			<= CLOSE_PAR && !syntax_exception(token1, token2))
		return (print_syntax_error(shell, token2->token_str));
	return (0);
}

static int	syntax_exception(t_token *token1, t_token *token2)
{
	if (token1->token == PIPE && (token2->token <= OUTPUT_APPEND))
		return (1);
	if (token1->token == OUTPUT_TRUNC && token2->token == PIPE)
	{
		if (token1->space_link == true)
			return (0);
		remove_token(token2);
		return (2);
	}
	if (token1->token == PIPE && token2->token == OPEN_PAR)
		return (3);
	if (token1->token == CLOSE_PAR && (token2->token < OPEN_PAR))
		return (4);
	if (token1->token == OPEN_PAR && (token2->token <= OUTPUT_APPEND))
		return (5);
	if ((token1->token == AND || token1->token == OR) && \
		(token2->token == OPEN_PAR || token2->token <= OUTPUT_APPEND))
		return (6);
	if ((token1->token == OPEN_PAR || token1->token == CLOSE_PAR) && \
		token2->token == token1->token)
		return (7);
	return (0);
}

int	cmd_before_or_after_parenthesis(t_global *shell, \
	t_token *token, enum e_token type)
{
	if (type < CLOSE_PAR && type > OUTPUT_APPEND)
		return (0);
	if (type >= CMD || type <= OUTPUT_APPEND)
	{
		while (token && (token->token <= OUTPUT_APPEND || token->token >= CMD))
			token = token->next;
		if (!token)
			return (0);
		if (token->token == OPEN_PAR)
			return (print_syntax_error(shell, token->token_str));
		return (0);
	}
	while (token && token->token <= OUTPUT_APPEND)
	{
		token = token->next;
		while (token && token->token >= CMD && token->space_link == false)
			token = token->next;
		token = token->next;
	}
	if (token && token->token >= CMD)
		return (print_syntax_error(shell, \
			token->origin_token_str));
	return (0);
}

int	early_closing_parenthesis(t_global *shell, t_token *token)
{
	if (token->token == OPEN_PAR)
		shell->nb_open_parenthesis++;
	else if (token->token == CLOSE_PAR)
		shell->nb_open_parenthesis--;
	if (shell->nb_open_parenthesis < 0)
		return (print_syntax_error(shell, token->token_str));
	return (0);
}
