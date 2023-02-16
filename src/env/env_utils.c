/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:10:33 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/16 11:40:44 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "errors.h"
#include "env.h"
#define INVALID_ID_SET	"=?_:{}[] |*-+!@^&#$<>\\,.:;"

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
	char 	*concat_pos;

	if (ft_isdigit(str[0]))
		return (0);
	i = 0;
	space_position = ft_strchr(str, '=');
	concat_pos = ft_strnstr(str, CONCAT_VAR, ft_strlen(str));
	if (concat_pos < space_position)
		space_position = concat_pos;
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

/**
 * @brief Search in env for variable `name`
 * 
 * @param env_list list of env variables
 * @param name variable name w/o `=`
 * @return t_list* list element containing `name` or `NULL` 
 */
t_list	*search_in_env(t_list *env_list, char *name)
{
	char	*s;
	int		len;

	len = 0;
	while (name[len] && name[len] != '=')
		len++;
	while (env_list)
	{
		s = (char *)(env_list->content);
		if (ft_strncmp(s, name, len) == 0 && \
			(s[len] == '\0' || s[len] == '=' || s[len] == '\n'))
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
		if (new == NULL)
		{
			free(new_content);
			error_exit_shell(shell, ERR_MALLOC);
		}
		ft_lstadd_back(&(shell->env_list), new);
		return ;
	}
	if (ft_strchr(new_var, '=') == NULL)
		return (free(new_content));
	free(search_result->content);
	search_result->content = new_content;
}

void	concat_env_variable(t_global *shell, char *var, t_list *search)
{
	char	*concat;
	char	*new_content;

	concat = ft_strnstr(var, CONCAT_VAR, ft_strlen(var));
	concat += ft_strlen(CONCAT_VAR);
	new_content = ft_strjoin_and_free(search->content, concat);
	if (new_content == NULL)
		error_exit_shell(shell, ERR_MALLOC);
	search->content = new_content;
}
