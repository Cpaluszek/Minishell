/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:41:33 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/16 10:19:33 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include "minishell.h"
#include "exec.h"

static void	close_all_file_descriptors_in_execution(t_list *fd_list);

int	exec_child(t_global *shell, t_token *command)
{
	char	**env;
	
	env = shell->env;
	if (exec_cmd_not_found(command))
		return (EXIT_FAILURE);
	// if (is_a_directory(command->cmd_path))
	// 	return (g_status);
	// if (command->fd_input)
	// 	dprintf(2,"fd_input %p (fd %d) from command %p (%s)\n", command->fd_input, *command->fd_input, command, command->cmd[0]);
	// if (command->fd_output)
	// 	dprintf(2,"fd_output %p (fd %d) from command %p (%s)\n", command->fd_output, *command->fd_output, command, command->cmd[0]);
	if (dup_fds(command))
		return (EXIT_FAILURE);
	// dprintf(2, "OK DUP IS FINISHED from command %p (%s)\n", command, command->cmd[0]);
	close_all_file_descriptors_in_execution(shell->block_fd_list);
	// dprintf(2, "OK CLOSING ALL FILES IS FINISHED from command %p (%s)\n\n", command, command->cmd[0]);
	if (command->make_a_pipe == 1 && close(command->pipe_fd[0]) == -1)
		perror(ERR_CLOSE);
	// dprintf(2, "close block command txt %d\n", close(3));
	execve(command->cmd_path, command->cmd, env);
	perror(ERR_EXEC);
	return (EXIT_FAILURE);
}

static void	close_all_file_descriptors_in_execution(t_list *fd_list)
{
	int	*fd;

	while (fd_list)
	{
		fd = (int *)fd_list->content;
		if (fd && *fd != -1)
			close(*fd);
		fd_list = fd_list->next;
	}
}
