/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:41:33 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/25 15:17:22 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	exec_child(t_token *token, char **env)
{
	if (dup_fds(token))
		return (EXIT_FAILURE);
	execve(token->cmd[0], token->cmd, env);
	perror(ERR_EXEC);
	return (EXIT_FAILURE);
}
