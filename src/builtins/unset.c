/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:48 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/26 09:51:32 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "env.h"

static void	remove_env_variable(t_global *shell, char *cmd, t_list *prev);

int	ft_unset(t_token *token, t_global *shell)
{
	int		i;
	int		ret_value;

	ret_value = 0;
	i = 1;
	while (token->cmd[i])
	{
		if (!is_valid_identifier(token->cmd[i]))
		{
			ft_printf_fd(STDERR, "unset: `%s' not a valid identifier\n", \
				token->cmd[i]);
			ret_value = EXIT_FAILURE;
		}
		else
			remove_env_variable(shell, token->cmd[i], NULL);
		i++;
	}
	return (ret_value);
}

static void	remove_env_variable(t_global *shell, char *cmd, t_list *prev)
{
	t_list	*env_list;
	char	*content;
	int		len;

	env_list = shell->env_list;
	while (env_list)
	{
		content = (char *)(env_list->content);
		len = 0;
		while (content[len] && content[len] != '=')
			len++;
		if (ft_strncmp(content, cmd, len) == 0)
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
	ft_lstdelone(env_list, free);
	update_env(shell);
}
