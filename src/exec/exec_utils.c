/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:45:52 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/15 18:28:59 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	wait_for_token_list(t_token *token)
{
	while (token)
	{
		if (token->token == CMD)
		{
			if (token->pid > 0)//&& token->exit_status != COMMAND_NOT_FOUND)
			{
				token->exit_status = 0;
				waitpid(token->pid, &token->exit_status, 0);
				if (WIFEXITED(token->exit_status))
					token->exit_status = WEXITSTATUS(token->exit_status);
				else if (WIFSIGNALED(token->exit_status))
					token->exit_status = 128 + WTERMSIG(token->exit_status);
			}
			g_status = token->exit_status;
		}
		token = token->next;
	}
}
