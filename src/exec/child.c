/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:41:33 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/21 18:28:07 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <unistd.h>

// Todo: execve fail
void	exec_child(t_token *token, char **env)
{
	if (token->fd_input != NULL)
	{
		dup2(*(token->fd_input), STDIN_FILENO);
		close(*(token->fd_input));
	}
	if (token->fd_output != NULL)
	{
		dup2(*(token->fd_output), STDOUT_FILENO);
		close(*(token->fd_output));
	}
	execve(token->cmd[0], token->cmd, env);
	exit(0);
}
