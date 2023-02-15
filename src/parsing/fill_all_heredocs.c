/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_all_heredocs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:53:37 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/02/15 20:37:26 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	fill_all_heredocs(t_global *shell)
{
	t_token	*token;
	
	token = shell->token_list;
	while (token)
	{
		if (token->token == HERE_DOC)
		{
			if (make_pipe_heredoc(shell, token))
			{
    			shell->command_line = HERE_DOC_PROBLEM;
    			return (EXIT_FAILURE);
			}
			add_fd_to_list(shell, &token->pipe_fd[0]);
		}
    	token = token->next;
	}
	return (EXIT_SUCCESS);
}
