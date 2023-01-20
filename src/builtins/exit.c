/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:39 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/18 16:51:04 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Exit the shell
// Optionnal parameter: exit status code
// Check for valid exit code
#include "structs.h"
#include "libft.h"
#include "errors.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "exec.h"

// static int	ft_isnum(char *str);

// exit N
// if N is not given - exit status code is the last executed command ($?)
// Todo: frees
// Todo: if no args - return last command exit status
// Note: what happens when exit command is called with multiples commands in line ?
int	ft_exit(t_token *token)
{
	(void) token;
	dprintf(STDERR_FILENO, "exit execution\n");
	return (0);
	// int	exit_value;

	// exit_value = 0;
	// if (args_number(token->cmd) < 2)
	// 	exit(exit_value);
	// else if (!ft_isnum(token->cmd[1]))
	// {
	// 	ft_putstr_fd("exit: numeric argument required", STDERR_FILENO);
	// 	exit(255);
	// }
	// else if (args_number(token->cmd) > 2)
	// {
	// 	ft_putstr_fd("exit: too many arguments", STDERR_FILENO);
	// 	return (1);
	// }
	// exit_value = ft_atoi(token->cmd[1]);
	// exit(exit_value);
}

// static int	ft_isnum(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (!ft_isdigit(str[i]))
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }
