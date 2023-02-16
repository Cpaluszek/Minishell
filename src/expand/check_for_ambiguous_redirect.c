/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_ambiguous_redirect.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 21:09:48 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/10 11:23:16 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include "parsing.h"

int	check_for_ambiguous_redirect(t_token *token)
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
