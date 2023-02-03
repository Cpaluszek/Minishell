/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:41:15 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/02/03 18:41:12 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

static int	syntax_exception(t_token *token1, t_token *token2);
static int	early_closing_parenthesis(t_global *shell, enum e_token token);
static int	cmd_before_or_after_parenthesis(t_global *shell, \
	t_token *token, enum e_token type);
int			print_syntax_error(t_global *shell, char *str);

//ATTENTION REMOVE DE CLEAR TOKEN LIST DANS SYNTAX ERROR, penseer a la remettre
int	syntax_checking(t_global *shell)
{
	t_token	*token;

	token = shell->token_list;
	// print_command_line(token);
	if (token->token == PIPE || token->token == AND || token->token == OR)
		return (print_syntax_error(shell, token->token_str));
	while (token)
	{
		if (token->token <= CLOSE_PAR && token->next && token->next->token \
			<= CLOSE_PAR && !syntax_exception(token, token->next))
			return (print_syntax_error(shell, token->next->token_str));
		else if (early_closing_parenthesis(shell, token->token))
			return (print_syntax_error(shell, token->token_str));
		else if (token->token <= OUTPUT_APPEND && !token->next && \
			shell->command_line != UNFINISHED_QUOTE && \
			shell->command_line != UNFINISHED_PARENTHESIS)
			return (print_syntax_error(shell, "newline"));
		token = token->next;
	}
	return (0);
}

int	syntax_checking_end(t_global *shell)
{
	t_token	*token;

	token = shell->token_list;

	while (token)
	{
		if ((token->token >= CLOSE_PAR) && \
			cmd_before_or_after_parenthesis(shell, token->next, token->token))
			return (1);
		token = token->next;
	}
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
		return (1);
	}
	if (token1->token == PIPE && token2->token == OPEN_PAR)
		return (1);
	if (token1->token == CLOSE_PAR && (token2->token != CLOSE_PAR))
		return (1);
	if ((token1->token == AND || token1->token == OR) && \
		(token2->token == OPEN_PAR || token2->token <= OUTPUT_APPEND))
		return (1);
	if ((token1->token == OPEN_PAR || token1->token == CLOSE_PAR) && \
		token2->token == token1->token)
		return (1);
	return (0);
}

static	int	cmd_before_or_after_parenthesis(t_global *shell, \
	t_token *token, enum e_token type)
{
	if (type >= CMD)
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
			token = token->next;
	if (!token)
		return (0);
	if (token->token >= CMD)
		return (print_syntax_error(shell, token->origin_token_str));
	return (0);
}


static int	early_closing_parenthesis(t_global *shell, enum e_token token)
{
	if (token == OPEN_PAR)
		shell->nb_open_parenthesis++;
	else if (token == CLOSE_PAR)
		shell->nb_open_parenthesis--;
	if (shell->nb_open_parenthesis < 0)
		return (1);
	return (0);
}

