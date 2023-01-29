/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:41:33 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/29 10:40:07 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

// Todo: close in case of execve error
int	exec_child(t_token *token, char **env)
{
	if (dup_fds(token))
		return (EXIT_FAILURE);
	if (token->make_a_pipe)
		if (close(token->pipe_fd[0]) == -1)
			perror(ERR_PIPE);
	execve(token->cmd[0], token->cmd, env);
	perror(ERR_EXEC);
	return (EXIT_FAILURE);
}
