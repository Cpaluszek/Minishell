/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 09:44:58 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/26 09:46:45 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

// Todo: move function to another file - common with parsing
char	*expand_env_var(t_global *shell, char *identifier)
{
	t_list	*env_var;
	char	*value;

	env_var = search_in_env(shell->env_list, identifier);
	if (env_var == NULL)
		return (identifier);
	value = ft_strchr((char *)(env_var->content), '=');
	if (value == NULL)
		return (ft_strdup(""));
	free(identifier);
	return (ft_strdup(value));
}