/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:07:07 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/23 13:24:12 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_list_functions.h"
#include "parsing.h"

void	setting_space_links_and_checking_parenthesis( \
			t_global *shell, t_token *token_list);

void	token_parsing(t_global *shell)
{
	t_token	*temp;
	t_token	*del;
	t_token	*splitted_token_list;

	temp = shell->token_list;
	while (temp)
	{
		if (temp->token == EMPTY && temp->str[0])
		{			
			splitted_token_list = create_sub_token_list(shell, temp->str);
			insert_token_list(&shell->token_list, temp, splitted_token_list);
			del = temp;
			temp = temp->next;
			ft_lstdelone_token(del);
		}
		else
			temp = temp->next;
	}
	setting_space_links_and_checking_parenthesis(shell, shell->token_list);
}

void	setting_space_links_and_checking_parenthesis(t_global *shell, \
	t_token *token)
{
	shell->nb_open_parenthesis = 0;
	while (token)
	{
		if (token->token != EMPTY)
			if (token->next && token->next->token != EMPTY)
				token->space_link = false;
		if (token->token == OPEN_PAR || token->token == CLOSE_PAR)
			shell->nb_open_parenthesis += 8 - token->token;
		token = token->next;
	}
	if (shell->nb_open_parenthesis > 0)
		shell->command_line = UNFINISHED_PARENTHESIS;
	else if (shell->command_line != UNFINISHED_QUOTE)
		shell->command_line = FINISHED_PARENTHESIS;
	shell->nb_open_parenthesis = 0;
}
