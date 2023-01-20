/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:33:31 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/18 17:02:42 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "exec.h"
#include <stdio.h>
#include <stdlib.h>

static int	search_builtins(t_token *token, t_builtin *arr, int *found, t_global *shell);

// Note: some builtins are found in PATH
int	parse_builtins(t_token *token, int *is_builtin, t_global *shell)
{
	static t_builtin	arr[] = {
	{"cd", &ft_cd},
	{"/usr/bin/echo", &ft_echo},
	{"/usr/bin/env", &ft_env},
	{"exit", &ft_exit},
	{"pwd", &ft_pwd},
	{"export", &ft_export},
	{"unset", &ft_unset},
	{NULL, NULL}
	};

	return (search_builtins(token, arr, is_builtin, shell));
}

static int	search_builtins(t_token *token, t_builtin *arr, int *found, t_global *shell)
{
	int	i;
	int	return_status;

	i = 0;
	return_status = 0;
	while (arr[i].name != NULL)
	{
		if (ft_strncmp(token->cmd[0], arr[i].name, ft_strlen(arr[i].name)) == 0)
		{
			*found = 1;
			return_status = arr[i].builtin(token, shell);
			return (return_status);
		}
		i++;
	}
	return (0);
}
