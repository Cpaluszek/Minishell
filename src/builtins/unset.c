/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:48 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/22 11:57:59 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "exec.h"
#include <stdio.h>
#include <unistd.h>

static void	remove_env_variable(t_global *shell, char *cmd);

// Todo: check error status code bash3.2
int	ft_unset(t_token *token, t_global *shell)
{
	int		i;

	i = 1;
	while (token->cmd[i])
	{
		if (!is_valid_identifier(token->cmd[i]))
		{
			ft_printf_fd(STDERR, "unset: `%s' not a valid identifier\n", \
				token->cmd[i]);
			g_status = 1;
		}
		else
		{
			remove_env_variable(shell, token->cmd[i]);
			g_status = 0;
		}
		i++;
	}
	return (0);
}

static void	remove_env_variable(t_global *shell, char *cmd)
{
	t_list	*env_list;
	t_list	*prev;
	char	*content;
	int		len;

	env_list = shell->env_list;
	prev = NULL;
	while (env_list)
	{
		content = (char *)(env_list->content);
		len = 0;
		while (content[len] && content[len] != '=')
			len++;
		if (ft_strncmp(content, cmd, len + 1) == 0)
			break ;
		prev = env_list;
		env_list = env_list->next;
	}
	if (env_list == NULL)
		return ;
	if (prev == NULL)
		shell->env_list = env_list->next;
	else
		prev->next = env_list->next;
	ft_lstdelone(env_list, *free);
}
