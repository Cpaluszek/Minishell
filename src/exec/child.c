/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:41:33 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/08 15:28:48 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

// TODO : erreur pour closing file
// TODO : utiliser une des fonctions stats pour chercker si c'est un directory
int	exec_child(t_token *token, char **env)
{
	if ((token->fd_input && *token->fd_input == -1) || \
		(token->fd_output && *token->fd_output == -1))
		return (EXIT_FAILURE);
	if (dup_fds(token))
		return (EXIT_FAILURE);
	// dprintf(STDERR, "%s: Attemp to close %p = %d\n\n",token->str, token->pipe_fd, token->pipe_fd[0]);
	if (token->make_a_pipe == 1 && close(token->pipe_fd[0]) == -1)
		perror(ERR_CLOSE);
	if (token->make_a_pipe == 2 && close(token->pipe_fd[1]) == -1)
		perror(ERR_CLOSE);
	execve(token->cmd_path, token->cmd, env);
	perror(ERR_EXEC);
	return (EXIT_FAILURE);
}
