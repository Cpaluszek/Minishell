/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:28:41 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/23 13:24:00 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			return (2);
		else if (token_at_end_of_command_line(shell, token))
			return (3);
		else if (cmd_before_or_after_parenthesis(shell, \
			token->next, token->token))
			return (4);
		token = token->next;
	}
	return (0);
}
