/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:39 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/16 12:49:57 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Exit the shell
// Optionnal parameter: exit status code
// Check for valid exit code
#include "minishell.h"
#include "exec.h"
#define EXIT_MSG "exit\n"
#define CODE_NON_NUM 2
#define LONG_MAX_STR "9223372036854775807"
#define LONG_MIN_STR "-9223372036854775808"

static int	ft_isnum(char *str);
static void	check_pipe_exit(t_global *shell, t_token *token, int exit_value);

int	ft_exit(t_token *token, t_global *shell)
{
	int	exit_value;

	if (!any_pipe_in_token_list(token))
		ft_putstr_fd(EXIT_MSG, STDOUT);
	if (args_number(token->cmd) < 2)
	{
		check_pipe_exit(shell, token, g_status);
		return (0);
	}
	else if (!ft_isnum(token->cmd[1]))
	{
		ft_printf_fd(STDERR, \
			"exit: %s: numeric argument required\n", token->cmd[1]);
		check_pipe_exit(shell, token, CODE_NON_NUM);
	}
	else if (args_number(token->cmd) > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR);
		return (1);
	}
	exit_value = ft_atoi(token->cmd[1]);
	check_pipe_exit(shell, token, exit_value);
	return (0);
}

static void	check_pipe_exit(t_global *shell, t_token *token, int exit_value)
{
	if (!any_pipe_in_token_list(token))
		exit_shell(shell, exit_value);
}

static int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !(i == 0 && str[i] == '-'))
			return (0);
		i++;
	}
	if (strlen(str) > ft_strlen(LONG_MIN_STR))
		return (0);
	else if (str[0] == '-' && ft_strlen(str) == ft_strlen(LONG_MIN_STR))
	{
		if (ft_strcmp(str, LONG_MIN_STR) > 0)
			return (0);
	}
	else if (ft_strlen(str) == ft_strlen(LONG_MAX_STR))
	{
		if (ft_strcmp(str, LONG_MAX_STR) > 0)
			return (0);
	}
	return (1);
}
