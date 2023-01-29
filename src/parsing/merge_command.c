/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:41:07 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/29 16:42:52 by Teiki            ###   ########.fr       */
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
		if (token->token > PIPE)
		{
			first_cmd = token;
			first_cmd->token = CMD;
			first_cmd->token_str = "CMD";
			while (token && token->token != PIPE)
			{
				if (token->token > PIPE)
					i++;
				token = token->next;
			}
			merge_all_cmd_token_between_pipe(shell, first_cmd, i);
			// dprintf(1,"\nAFTER ONE MERGE COMMAND (i = %d)", i);
			// print_command_line(shell->token_list);
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
	while (token && token->token != PIPE)
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
