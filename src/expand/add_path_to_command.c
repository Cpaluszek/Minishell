/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path_to_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:03:35 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/23 13:21:36 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static int	find_path(t_global *shell, t_token *token, char *cmd);

/*
	Check access and join the path to the first command argument.
*/
void	add_path_to_command_token(t_global *shell, t_token *token_list)
{
	t_token	*token;

	token = token_list;
	while (token)
	{
		if (shell->path && token->token == CMD && \
			access(token->cmd[0], F_OK) != 0 && \
			!ft_is_inside('/', token->cmd[0]) && token->cmd[0][0])
			find_path(shell, token, token->cmd[0]);
		else if (token->token == CMD)
		{
			token->cmd_path = ft_strdup(token->cmd[0]);
			test_failed_malloc(shell, token->cmd_path);
		}
		token = token->next;
	}
}

/* 
	Function that will try each possible path for command input argument.
*/
static int	find_path(t_global *shell, t_token *token, char *cmd)
{
	int		i;
	char	*test_path;
	char	**path;

	path = shell->path;
	i = 0;
	while (path[i])
	{
		test_path = ft_strjoin(path[i], "/");
		test_failed_malloc(shell, test_path);
		test_path = ft_strjoin_and_free(test_path, cmd);
		test_failed_malloc(shell, test_path);
		if (access(test_path, F_OK) == 0)
		{
			token->cmd_path = test_path;
			return (1);
		}
		free(test_path);
		i++;
	}
	token->cmd_path = ft_strdup(cmd);
	test_failed_malloc(shell, token->cmd_path);
	return (0);
}
