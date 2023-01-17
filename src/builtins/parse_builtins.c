/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:33:31 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/17 15:08:40 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "exec.h"
#include <stdlib.h>

static int	search_builtins(t_token *token, t_builtin *arr, int *is_builtin);

int	parse_builtins(t_token *token, int *is_builtin)
{
	static t_builtin	arr[] = {
	{"cd", "cd [directory]", &ft_cd},
	{"echo", "echo [-n] [arg...]", &ft_echo},
	{"env", "env", &ft_env},
	{"exit", "exit [num]", &ft_exit},
	{"pwd", "pwd", &ft_pwd},
	{"export", "export [name[=word]]", &ft_export},
	{"unset", "unset [name]", &ft_unset},
	{NULL, NULL, NULL}
	};

	return (search_builtins(token, arr, is_builtin));
}

static int	search_builtins(t_token *token, t_builtin *arr, int *is_builtin)
{
	int	i;
	int	return_status;

	i = 0;
	return_status = 0;
	while (arr[i].name != NULL)
	{
		if (ft_strcmp(token->cmd[0], arr[i].name) == 0)
		{
			*is_builtin = 1;
			return_status = arr[i].builtin(token);
			// Todo: check return status code and print usage
			return (return_status);
		}
		i++;
	}
	return (0);
}
