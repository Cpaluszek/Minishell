/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:39 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/18 11:50:23 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Exit the shell
// Optionnal parameter: exit status code
// Check for valid exit code
#include "structs.h"
#include "libft.h"
#include "errors.h"
#include <stdlib.h>
#include <unistd.h>

static int	ft_isnum(char *str);
static int	args_number(char **args);

// exit N
// if N is not given - exit status code is the last executed command ($?)
// Todo: frees
// Todo: if no args - return last command exit status
int	ft_exit(t_token *token)
{
	int	exit_value;

	exit_value = 0;
	if (args_number(token->cmd) < 2)
		exit(exit_value);
	else if (!ft_isnum(token->cmd[1]))
	{
		ft_putstr_fd(STDERR_FILENO, "exit: numeric argument required");
		exit(255);
	}
	else if (args_number(token->cmd) > 2)
	{
		ft_putstr_fd(STDERR_FILENO, "exit: too many arguments");
		return (1);
	}
	exit_value = ft_atoi(token->cmd[1]);
	exit(exit_value);
}

static int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	args_number(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}
