/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:21:56 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/17 13:15:35 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

static int	is_a_directory(char *path);

int	exec_cmd_not_found(t_token *token)
{
	// TODO: WTF !!!
	// dprintf(2, "CMD not found : %s\n", token->cmd_path);
	if (ft_strchr(token->cmd_path, '/') != NULL && (access(token->cmd_path, \
		X_OK)) == -1 && access(token->cmd_path, F_OK) == 0)
	{
		ft_printf_fd(2, "msh: %s: Permission denied\n", token->cmd[0]);
		g_status = 126;
		return (EXIT_FAILURE);
	}
	else if (access(token->cmd_path, F_OK) != 0 && \
		ft_strchr(token->cmd_path, '/') != NULL)
	{
		ft_printf_fd(STDERR, "msh: %s: No such file or directory\n", \
			token->cmd[0]);
		g_status = 127;
		return (EXIT_FAILURE);
	}
	else if (is_a_directory(token->cmd_path))
		return (EXIT_FAILURE);
	else if (access(token->cmd_path, X_OK) == -1)
	{
		ft_printf_fd(STDERR, "msh: %s: command not found\n", token->cmd[0]);
		g_status = COMMAND_NOT_FOUND;
		return (EXIT_FAILURE);
	}
	return (0);
}

int	print_execution_error(char *name)
{
	ft_printf_fd(2, "msh: %s: %s\n", name, strerror(errno));
	return (-1);
}

static int	is_a_directory(char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
	{
		ft_printf_fd(2, "msh: %s: Is a directory\n", path);
		g_status = 126;
		return (1);
	}
	return (0);
}
