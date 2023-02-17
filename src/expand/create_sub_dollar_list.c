/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sub_dollar_list.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:17:56 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/16 19:40:07 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "minishell.h"

t_token	*create_sub_dollar_list(t_global *shell, t_token *old_token, char *str)
{
	int				i;
	t_token			*token_list;

	token_list = NULL;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] != ' ')
			i++;
		if (i != 0 && new_token(&token_list, str, i, CMD))
			error_exit_shell(shell, ERR_MALLOC);
		if (!str[i])
			break ;
		while (str[i] && str[i] == ' ')
			i++;
		str = &str[i];
		i = 0;
	}
	assign_ambiguous_redirect(shell, old_token, token_list);
	return (token_list);
}
