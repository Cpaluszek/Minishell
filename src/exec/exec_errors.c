/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:21:56 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/10 17:56:44 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

void	exec_cmd_not_found(t_token *token)
{
	if (ft_strchr(token->cmd_path, '/') != NULL)
		ft_printf_fd(STDERR, "%s: No such file or directory\n", \
			token->cmd[0]);
	else
		ft_printf_fd(STDERR, "command not found: %s\n", token->cmd[0]);
	token->exit_status = COMMAND_NOT_FOUND;
	close_token_pipes(token);
}

void	exec_cmd_error(t_global *shell, char *err, t_token *token)
{
	perror(err);
	if (ft_strcmp(err, ERR_PIPE) != 0)
		close_token_pipes(token);
	exit_shell(shell, EXIT_FAILURE);
}
