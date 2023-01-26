/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:10:33 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/26 13:46:13 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
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

// TODO: check $?
/**
 * @brief Search in env for variable `name`
 * 
 * @param env_list list of env variables
 * @param name variable name with `=`. Example `HOME=`
 * @return t_list* list element containing `name` or `NULL` 
 */
t_list	*search_in_env(t_list *env_list, char *name)
{
	char	*content;
	int		len;

	while (env_list)
	{
		content = (char *)(env_list->content);
		len = 0;
		while (content[len] && content[len] != '=')
			len++;
		if (ft_strncmp(content, name, len + 1) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

void	add_env_variable(t_global *shell, char *new_var)
{
	char	*new_content;
	t_list	*search_result;
	t_list	*new;

	new_content = ft_strdup(new_var);
	if (new_content == NULL)
		error_exit_shell(shell, ERR_MALLOC);
	search_result = search_in_env(shell->env_list, new_var);
	if (search_result == NULL)
	{
		new = ft_lstnew(new_content);
		ft_lstadd_back(&(shell->env_list), new);
	}
	else
	{
		free(search_result->content);
		search_result->content = new_content;
	}
}
