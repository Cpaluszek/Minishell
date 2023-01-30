/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:44:08 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/29 19:46:18 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "token_list_functions.h"

static void	insert_temp_cmd_list(t_global *shell, t_token *token, char **cmd);

void	split_command_token(t_global *shell)
{
	t_token	*token;
	t_token	*temp;

	token = shell->token_list;
	while (token)
	{
		if (token->token == CMD)
		{
			token->cmd = ft_split(token->str, ' ');
			test_failed_malloc(shell, token->cmd);
			insert_temp_cmd_list(shell, token, token->cmd);
			temp = token;
			token = token->next;
			ft_lstdelone_token(temp);
		}
		else
			token = token->next;
	}
}

static void	insert_temp_cmd_list(t_global *shell, t_token *token, char **cmd)
{
	t_token	*new_cmd_list;
	t_token	*new;
	char	*cmd_str;
	int		i;

	new_cmd_list = NULL;
	i = 0;
	while (cmd[i])
	{
		cmd_str = ft_strdup(cmd[i]);
		test_failed_malloc(shell, cmd_str);
		new = ft_lstnew_token(cmd_str, CMD);
		test_failed_malloc(shell, new);
		ft_lstadd_back_token(&new_cmd_list, new);
		i++;
	}
	insert_token_list(shell, token, new_cmd_list);
}