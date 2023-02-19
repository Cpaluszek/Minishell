/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:45:52 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/19 14:10:58 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Wait for all command token in the concerning block.
 * The global exit code will be set as the return exit code of 
 * the last command executed.
 * 
 */
void	wait_for_token_list(t_token *token)
{
	while (token)
	{
		if (token->token == CMD)
		{
			if (token->pid > 0)
			{
				token->exit_status = 0;
				waitpid(token->pid, &token->exit_status, 0);
				if (WIFEXITED(token->exit_status))
					token->exit_status = WEXITSTATUS(token->exit_status);
				else if (WIFSIGNALED(token->exit_status))
					token->exit_status = 128 + WTERMSIG(token->exit_status);
			}
			g_status = token->exit_status;
			// dprintf(1, "EXIT FROM WAITING token_list : %d\n", g_status);
		}
		token = token->next;
	}
}
