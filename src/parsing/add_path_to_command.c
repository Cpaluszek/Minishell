/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path_to_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:59:33 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/01/23 14:55:52 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include <unistd.h>

int	find_path(char **cmd, char **path);

/*
	Function that check the access of each command input argument.
	If access isn't valid, it will call the finding path function.
	If there is no valid path in the pathironment, it will display an error.
*/
void	add_path_to_command_token(t_global *shell)
{
	t_token	*token_list;

	if (!shell->path)
		return ;
	token_list = shell->token_list;
	while (token_list)
	{
		if (!(token_list->token != CMD || !token_list->cmd[0]) && \
			(access(token_list->cmd[0], X_OK) != 0))
		{
			if (find_path(token_list->cmd, shell->path) == -1)
				error_exit_shell(shell, ERR_MALLOC);
		}
		token_list = token_list->next;
	}
}

/* 
	Function that will try each possible path for command input argument.
*/
int	find_path(char **cmd, char **path)
{
	int		i;
	char	*test_path;

	i = 0;
	while (path[i])
	{
		test_path = ft_strjoin(path[i], "/");
		if (!test_path)
			return (-1);
		test_path = ft_strjoin_and_free(test_path, *cmd);
		if (!test_path)
			return (-1);
		if (access(test_path, X_OK) == 0)
		{
			free(*cmd);
			*cmd = test_path;
			return (1);
		}
		free(test_path);
		i++;
	}
	return (0);
}
