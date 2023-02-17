/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:41:33 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/17 16:34:34 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

static void	close_all_file_descriptors_in_execution(t_list *fd_list);

int	exec_child(t_global *shell, t_token *command, t_token *pipe)
{
	char	**env;

	env = shell->env;
	if (exec_cmd_not_found(command))
		return (EXIT_FAILURE);
	if (dup_fds(command))
		return (EXIT_FAILURE);
	if (pipe)
		close(pipe->pipe_fd[0]);
	close_all_file_descriptors_in_execution(shell->block_fd_list);
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
