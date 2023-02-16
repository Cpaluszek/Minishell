/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:39:52 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/16 14:51:35 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_list_functions.h"
#include "parsing.h"

static void	setting_space_links_and_checking_parenthesis( \
			t_global *shell, t_token *token_list);

void	token_parsing(t_global *shell)
{
	t_token	*temp;
	t_token	*del;
	t_token	*splitted_token_list;

	temp = shell->token_list;
	while (temp)
	{
		if ((temp->token == EMPTY || temp->token == DOLLAR) && temp->str[0])
		{
			if (temp->token == EMPTY)
				splitted_token_list = create_sub_token_list(shell, temp->str);
			else
				splitted_token_list = create_sub_dollar_list(shell, \
					temp, temp->str);
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

static void	setting_space_links_and_checking_parenthesis(t_global *shell, \
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
