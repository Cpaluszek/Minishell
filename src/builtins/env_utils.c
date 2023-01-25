/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:10:33 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/25 11:52:04 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "errors.h"
#define INVALID_ID_SET "=?_:{}[]"

/**
 * @brief check if the input is a valid identifier. A valid identifier can only
 * 	contains letters, underscores and numbers and can't begin with a number
 * 
 * @param str export command argument
 * @return 0 if it's not valid, 1 otherwise
 */
int	is_valid_identifier(char *str)
{
	int		i;
	char	*space_position;

	if (ft_isdigit(str[0]))
		return (0);
	i = 0;
	space_position = ft_strchr(str, '=');
	while (str + i < space_position)
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && \
			ft_strchr(INVALID_ID_SET, str[i]) != NULL)
			return (0);
		i++;
	}
	return (1);
}

void	update_env(t_global *shell)
{
	int		i;
	char	*dup;
	t_list	*env_list;

	ft_free_split(shell->env);
	shell->env = malloc(sizeof(char *) * (ft_lstsize(shell->env_list) + 1));
	if (shell->env == NULL)
		error_exit_shell(shell, ERR_MALLOC);
	i = 0;
	env_list = shell->env_list;
	while (env_list)
	{
		dup = ft_strdup(env_list->content);
		if (dup == NULL)
		{
			ft_free_split(shell->env);
			error_exit_shell(shell, ERR_MALLOC);
		}
		shell->env[i] = dup;
		i++;
		env_list = env_list->next;
	}
	shell->env[i] = NULL;
}

t_list	*search_in_env(t_list *env_list, char *identifier)
{
	char	*content;
	int		len;

	while (env_list)
	{
		content = (char *)(env_list->content);
		len = 0;
		while (content[len] && content[len] != '=')
			len++;
		if (ft_strncmp(content, identifier, len + 1) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}
