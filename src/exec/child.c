/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:41:33 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/18 19:19:05 by Teiki            ###   ########.fr       */
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
	close_heredocs_file_descriptors(shell->block_fd_list);
	close_block_redirection(block);
	execve(command->cmd_path, command->cmd, env);
	perror(ERR_EXEC);
	return (EXIT_FAILURE);
}
