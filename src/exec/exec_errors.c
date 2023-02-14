/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:21:56 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/14 00:41:12 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

int	exec_cmd_not_found(t_token *token)
{
	if (errno == EACCES)
	{
		ft_printf_fd(2, "msh: %s: Permission denied\n", token->cmd_path);
		g_status = 126;
		return (g_status);
	}
	else if (errno == ENOENT && ft_strchr(token->cmd_path, '/') != NULL)
		ft_printf_fd(STDERR, "msh: %s: No such file or directory\n", \
			token->cmd[0]);
	else
		ft_printf_fd(STDERR, "msh: %s :command not found\n", token->cmd[0]);
	token->exit_status = COMMAND_NOT_FOUND;
	close_token_pipes(token);
	return (EXIT_FAILURE);
}

void	exec_cmd_error(t_global *shell, char *err, t_token *token)
{
	perror(err);
	if (ft_strcmp(err, ERR_PIPE) != 0)
		close_token_pipes(token);
	exit_shell(shell, EXIT_FAILURE);
}
