/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:41:33 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/24 10:33:25 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
// TODO : checker l'acces au fichier : si fd = -1 -> 
// TODO : erreur pour closing file
int	exec_child(t_token *token, char **env)
{
	if (token->fd_input != NULL)
	{
		if (dup2(*(token->fd_input), STDIN) == -1)
		{
			perror(ERR_DUP2);
			close(*(token->fd_input));
			return (1);
		}
		close(*(token->fd_input));
	}
	if (token->fd_output != NULL)
	{
		if (dup2(*(token->fd_output), STDOUT) == -1)
		{
			perror(ERR_DUP2);
			close(*(token->fd_output));
			return (1);
		}
		close(*(token->fd_output));
	}
	execve(token->cmd[0], token->cmd, env);
	perror(ERR_EXEC);
	return (2);
}
