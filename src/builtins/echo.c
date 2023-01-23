/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:33 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/23 11:32:29 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Writes argument to STDOUT
// Option -n: print without trailing newline
// The echo utility exits 0 on success, and >0 if an error occurs.
#include "structs.h"
#include "exec.h"
#define NL "-n"

static int	echo_option(t_token *t, int *arg_i);

// Todo: crash with e"cho" test
// Note: parsing problem with echo "-n test"
// Note: what is echo $$
int	ft_echo(t_token *token, t_global *shell)
{
	int	arg_index;
	int	new_line;

	(void) shell;
	arg_index = 1;
	new_line = echo_option(token, &arg_index);
	while (token->cmd[arg_index])
	{
		ft_putstr_fd(token->cmd[arg_index], STDOUT);
		if (token->cmd[arg_index + 1])
			ft_putstr_fd(" ", STDOUT);
		arg_index++;
	}
	if (new_line)
		ft_putstr_fd("\n", STDOUT);
	return (0);
}

// Skip all "-n" and "-nnnnn"
static int	echo_option(t_token *t, int *arg_i)
{
	int	new_line;
	int	len;
	int	j;

	new_line = 1;
	len = ft_strlen(NL);
	while (t->cmd[*arg_i] && ft_strncmp(t->cmd[*arg_i], NL, len) == 0)
	{
		j = len;
		while (t->cmd[*arg_i][j] && t->cmd[*arg_i][j] == 'n')
			j++;
		if (t->cmd[*arg_i][j] && t->cmd[*arg_i][j] != '\0')
			return (new_line);
		else if (*arg_i == 1)
			new_line = 0;
		(*arg_i)++;
	}
	return (new_line);
}
