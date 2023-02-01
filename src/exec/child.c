/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:41:33 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/01 14:02:04 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

// TODO : erreur pour closing file
//TODO : envisager de cnager make a pipe en int pour avoir acces a une troisieme valeur : own_pipe?
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
	execve(token->cmd[0], token->cmd, env);
	perror(ERR_EXEC);
	return (EXIT_FAILURE);
}
