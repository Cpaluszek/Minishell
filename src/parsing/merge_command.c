/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:41:07 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/03 18:24:20 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	merge_all_cmd_token_between_pipe(t_global *shell, \
t_token *first_cmd,	int size_cmd_tab);

void	merge_command(t_global *shell)
{
	t_token	*token;
	t_token	*first_cmd;
	int		i;

	token = shell->token_list;
	while (token)
	{
		i = 0;
		if (token->token > CLOSE_PAR)
		{
			first_cmd = token;
			while (token && (token->token < PIPE || token->token > CLOSE_PAR))
			{
				if (token->token > CLOSE_PAR)
					i++;
				token = token->next;
			}
			merge_all_cmd_token_between_pipe(shell, first_cmd, i);
		}
		else
			token = token->next;
	}
}

static void	merge_all_cmd_token_between_pipe(t_global *shell, \
t_token *first_cmd,	int size_cmd_tab)
{
	t_token	*token;
	t_token	*temp;
	int		i;

	first_cmd->cmd = malloc(sizeof(char *) * (size_cmd_tab + 1));
	test_failed_malloc(shell, first_cmd->cmd);
	first_cmd->cmd[0] = ft_strdup(first_cmd->str);
	test_failed_malloc(shell, first_cmd->cmd[0]);
	token = first_cmd->next;
	i = 1;
	while (token && (token->token < PIPE || token->token > CLOSE_PAR))
	{
		if (token->token == CMD || token->token == QUOTE || \
			token->token == DQUOTE)
		{
			first_cmd->cmd[i] = ft_strdup(token->str);
			test_failed_malloc(shell, first_cmd->cmd[i++]);
			temp = token;
			token = token->next;
			remove_token(temp);
		}
		else
			token = token->next;
	}
	first_cmd->cmd[i] = NULL;
}
