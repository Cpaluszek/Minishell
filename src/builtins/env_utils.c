/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:10:33 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/21 17:10:33 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include "exec.h"

void	update_env(t_global *shell)
{
	int		i;
	char	*dup;
	t_list	*env_list;

	ft_free_split(shell->env);
	shell->env = malloc(sizeof(char *) * (ft_lstsize(shell->env_list) + 1));
	if (shell->env == NULL)
		error_exit_exec(shell, "Alloc error");
	i = 0;
	env_list = shell->env_list;
	while (env_list)
	{
		dup = ft_strdup(env_list->content);
		if (dup == NULL)
		{
			ft_free_split(shell->env);
			error_exit_exec(shell, "Alloc error");
		}
		shell->env[i] = dup;
		i++;
		env_list = env_list->next;
	}
	shell->env[i] = NULL;
}

int	cmp_str(void *data1, void *data2)
{
	if (data1 && data2)
		return (ft_strcmp((char *)data1, (char *)data2));
	return (0);
}

void	*copy_content_str(void *entry)
{
	char	*str;

	str = (char *)entry;
	if (str == NULL)
		return (NULL);
	return (ft_strdup(str));
}

/**
 * @brief check if the input is a valid identifier. A valid identifier can only
 * 	contains letters, underscores and numbers and can't begin with a number
 * 
 * @param str export command argument
 * @return 0 if it's not valid, 1 otherwise
 */
int	is_valid_identifier(char *str)
{
	int	i;

	if (ft_isdigit(str[0]))
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

t_list	*search_identifier(t_list *env_list, char *identifier)
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
