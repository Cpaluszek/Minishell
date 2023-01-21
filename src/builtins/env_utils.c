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

int	is_allowed_char(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '_');
}
