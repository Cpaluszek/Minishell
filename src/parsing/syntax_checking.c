/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:41:15 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/02/09 22:10:53 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "syntax.h"

int	syntax_checking(t_global *shell)
{
	t_token	*token;

	token = shell->token_list;
	if (!token)
		return (0);
	if (token->token == PIPE || token->token == AND || token->token == OR)
		return (print_syntax_error(shell, token->token_str));
	while (token)
	{
		if (two_tokens_in_a_row(shell, token, token->next))
			return (1);
		else if (early_closing_parenthesis(shell, token))
			return (1);
		else if (token_at_end_of_command_line(shell, token))
			return (1);
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
		if ((token->token >= CLOSE_PAR || token->token <= OUTPUT_APPEND) && \
			cmd_before_or_after_parenthesis(shell, token->next, token->token))
			return (1);
		token = token->next;
	}
	return (0);
}
