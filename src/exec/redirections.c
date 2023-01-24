/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:39:33 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/24 13:08:43 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

// Todo: Protect opens
void	setup_all_redirections(t_global *shell, t_token *tok)
{
	while (tok)
	{
		if (tok->token == INPUT)
			tok->fd_file = open(tok->str, O_RDONLY);
		else if (tok->token == HERE_DOC)
		{
			here_doc(shell, tok);
			tok->fd_file = open(HERE_DOC_TMP, O_RDONLY);
		}
		else if (tok->token == OUTPUT_TRUNC)
			tok->fd_file = open(tok->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (tok->token == OUTPUT_APPEND)
			tok->fd_file = open(tok->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		tok = tok->next;
	}
}

// Todo: protect close
void	close_all_redirections(t_token *tok)
{
	while (tok)
	{
		if (tok->token == INPUT || tok->token == OUTPUT_APPEND || \
			tok->token == OUTPUT_TRUNC)
		{
			close(tok->fd_file);
		}
		else if (tok->token == HERE_DOC)
		{
			unlink(HERE_DOC_TMP);
		}
		tok = tok->next;
	}
}

void	close_redirections(t_token *tok)
{
	if (tok->token == INPUT || tok->token == OUTPUT_APPEND || \
			tok->token == OUTPUT_TRUNC)
		close(tok->fd_file);
}
