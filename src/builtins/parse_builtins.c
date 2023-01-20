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

static int	search_builtins(t_token *token, t_builtin *arr, int *is_builtin);

// Note: some builtins are found in PATH
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

int	args_number(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

static int	search_builtins(t_token *token, t_builtin *arr, int *is_builtin)
{
	int	i;
	int	return_status;

	i = 0;
	return_status = 0;
	while (arr[i].name != NULL)
	{
		if (ft_strncmp(token->cmd[0], arr[i].name, ft_strlen(arr[i].name)) == 0)
		{
			*is_builtin = 1;
			return_status = arr[i].builtin(token);
			if (return_status)
				printf("%s\n", arr->usage);
			return (return_status);
		}
		i++;
	}
	return (0);
}
