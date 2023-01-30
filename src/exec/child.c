/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:41:33 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/30 09:47:53 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
// TODO : checker l'acces au fichier : si fd = -1 -> 
// TODO : erreur pour closing file
int	exec_child(t_token *token, char **env)
{
	if (dup_fds(token))
		return (EXIT_FAILURE);
	if (token->make_a_pipe)
		if (close(token->pipe_fd[0]) == -1)
			perror(ERR_PIPE);
	execve(token->cmd[0], token->cmd, env);
	perror(ERR_EXEC);
	if (token->make_a_pipe && close(token->pipe_fd[1]) == -1)
		perror(ERR_CLOSE);
	if (token->prev && token->prev->make_a_pipe)
		if (close(token->prev->pipe_fd[0]) == -1)
			perror(ERR_CLOSE);
	return (EXIT_FAILURE);
}
