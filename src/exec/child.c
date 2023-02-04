/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:41:33 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/02 15:05:48 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

// TODO : erreur pour closing file
//TODO : utiliser une des fonctions stats pour chercker si c'est un directory
int	exec_child(t_token *token, char **env)
{
	if ((token->fd_input && *token->fd_input == -1) || \
		(token->fd_output && *token->fd_output == -1))
		return (EXIT_FAILURE);
	if (dup_fds(token))
		return (EXIT_FAILURE);
	if (token->make_a_pipe)
		if (token->make_a_pipe == true && close(token->pipe_fd[0]) == -1)
			perror(ERR_CLOSE);
	execve(token->cmd_path, token->cmd, env);
	perror(ERR_EXEC);
	return (EXIT_FAILURE);
}
