/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_merging.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:04:39 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/23 13:22:26 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "token_list_functions.h"
#include "libft.h"
#include <stdio.h>

static void	merge_all_cmd_token_between_pipe(t_global *shell, \
			t_token *first_cmd,	int size_cmd_tab);
static void	merge_redirection(t_global *shell, t_token *head_list);
static void	merge_command(t_global *shell, t_token *head_list);

void	token_merging(t_global *shell, t_token *head_list)
{
	t_token	*token;

	merge_redirection(shell, head_list);
	merge_command(shell, head_list);
	token = head_list;
	while (token)
	{
		if (token->token > CMD)
			token->token = CMD;
		token = token->next;
	}
}

static void	merge_redirection(t_global *shell, t_token *head_list)
{
	t_token	*token;
	t_token	*temp;

	token = head_list;
	while (token)
	{
		if (token->token <= OUTPUT_APPEND && token->token != HERE_DOC \
			&& token->next)
		{
			token->str = ft_strdup(token->next->str);
			test_failed_malloc(shell, token->str);
			temp = token->next;
			remove_token(temp);
		}
		token = token->next;
	}
}

static void	merge_command(t_global *shell, t_token *head_list)
{
	t_token	*token;
	t_token	*first_cmd;
	int		size_cmd_tab;

	token = head_list;
	while (token)
	{
		size_cmd_tab = 0;
		if (token->token > CLOSE_PAR)
		{
			first_cmd = token;
			while (token && (token->token < PIPE || token->token > CLOSE_PAR))
			{
				if (token->token > CLOSE_PAR)
					size_cmd_tab++;
				token = token->next;
			}
			merge_all_cmd_token_between_pipe(shell, first_cmd, size_cmd_tab);
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
		if (token->token >= CMD)
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
