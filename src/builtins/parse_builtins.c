/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:33:31 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/25 15:26:06 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

static int	search_builtin(t_token *t, t_builtin *arr, int *found, t_global *s);

// Todo: remove absolute PATH - some builtins are found in PATH
int	parse_builtins(t_token *token, int *is_builtin, t_global *shell)
{
	static t_builtin	arr[] = {
	{"cd", &ft_cd},
	{"/usr/bin/cd", &ft_cd},
	{"/usr/bin/echo", &ft_echo},
	{"/bin/echo", &ft_echo},
	{"env", &ft_env},
	{"/usr/bin/env", &ft_env},
	{"exit", &ft_exit},
	{"pwd", &ft_pwd},
	{"/bin/pwd", &ft_pwd},
	{"export", &ft_export},
	{"unset", &ft_unset},
	{NULL, NULL}
	};

	return (search_builtin(token, arr, is_builtin, shell));
}

static int	search_builtin(t_token *t, t_builtin *arr, int *found, t_global *s)
{
	int	i;
	int	return_status;

	i = 0;
	return_status = 0;
	while (arr[i].name != NULL)
	{
		if (ft_strncmp(t->cmd[0], arr[i].name, ft_strlen(arr[i].name)) == 0)
		{
			*found = 1;
			return_status = arr[i].builtin(t, s);
			return (return_status);
		}
		i++;
	}
	return (0);
}
