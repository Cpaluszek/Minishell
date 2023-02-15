/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:21:56 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/15 13:32:25 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include <string.h>
#include <errno.h>

int	exec_cmd_not_found(t_token *token)
{
	if (errno == EACCES)
	{
		ft_printf_fd(2, "msh: %s: Permission denied\n", token->cmd_path);
		token->exit_status = 126;
		return (EXIT_FAILURE);
	}
	else if (errno == ENOENT && ft_strchr(token->cmd_path, '/') != NULL)
		ft_printf_fd(STDERR, "msh: %s: No such file or directory\n", \
			token->cmd[0]);
	else
		ft_printf_fd(STDERR, "msh: %s :command not found\n", token->cmd[0]);
	g_status = COMMAND_NOT_FOUND;
	return (EXIT_FAILURE);
}
