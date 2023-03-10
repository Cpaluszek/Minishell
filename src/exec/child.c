/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:01:33 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/23 13:01:33 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	exec_child(t_global *shell, t_token *command, t_token *pipe, \
	t_block *block)
{
	char	**env;

	if (pipe)
		close(pipe->pipe_fd[0]);
	env = shell->env;
	if (exec_cmd_not_found(command))
		return (EXIT_FAILURE);
	if (dup_fds(command))
		return (EXIT_FAILURE);
	close_heredocs_file_descriptors(shell->heredoc_fd_list);
	close_block_redirection(block);
	execve(command->cmd_path, command->cmd, env);
	print_execution_error(command->cmd[0]);
	g_status = EXIT_FAILURE;
	return (EXIT_FAILURE);
}
