/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:41:33 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/30 14:40:19 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

// TODO : erreur pour closing file
int	exec_child(t_token *token, char **env)
{
	if ((token->fd_input && *token->fd_input == -1) || \
		(token->fd_output && *token->fd_output == -1))
		return (EXIT_FAILURE);
	if (dup_fds(token))
		return (EXIT_FAILURE);
	if (token->make_a_pipe)
		if (close(token->pipe_fd[0]) == -1)
			perror(ERR_CLOSE);
	execve(token->cmd[0], token->cmd, env);
	perror(ERR_EXEC);
	return (EXIT_FAILURE);
}
