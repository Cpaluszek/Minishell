/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:39 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/23 14:56:58 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Exit the shell
// Optionnal parameter: exit status code
// Check for valid exit code
#include "minishell.h"
#include "exec.h"
#define EXIT_MSG "exit\n"
#define CODE_NON_NUM 2

static int	ft_isnum(char *str);

// Note: what happens when exit command is called with 
// multiples commands in line ?
int	ft_exit(t_token *token, t_global *shell)
{
	int	exit_value;

	ft_putstr_fd(EXIT_MSG, STDOUT);
	if (args_number(token->cmd) < 2)
		exit(g_status);
	else if (!ft_isnum(token->cmd[1]))
	{
		ft_printf_fd(STDERR, \
			"exit: %s: numeric argument required\n", token->cmd[1]);
		exit_shell(shell, CODE_NON_NUM);
	}
	else if (args_number(token->cmd) > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR);
		return (1);
	}
	exit_value = ft_atoi(token->cmd[1]);
	exit_shell(shell, exit_value);
	return (0);
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
