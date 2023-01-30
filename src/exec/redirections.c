/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:39:33 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/30 14:40:10 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "input.h"

int	setup_all_redirections(t_global *shell, t_token *tok)
{
	while (tok)
	{
		if (tok->token == INPUT)
			tok->fd_file = open(tok->str, O_RDONLY);
		else if (tok->token == HERE_DOC)
		{
			if (here_doc(shell, tok) != 0)
				return (1);
			tok->fd_file = open(HERE_DOC_TMP, O_RDONLY);
		}
		else if (tok->token == OUTPUT_TRUNC)
			tok->fd_file = open(tok->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (tok->token == OUTPUT_APPEND)
			tok->fd_file = open(tok->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if ((tok->token == 0 || tok->token == 3 || \
			tok->token == 2) && tok->fd_file == -1)
			perror(tok->str);
		tok = tok->next;
	}
	return (0);
}

void	close_all_redirections(t_token *tok)
{
	while (tok)
	{
		if (tok->token == INPUT || tok->token == OUTPUT_APPEND || \
			tok->token == OUTPUT_TRUNC)
		{
			if (tok->fd_file != -1 && close(tok->fd_file) == -1)
				perror(ERR_CLOSE);
		}
		else if (tok->token == HERE_DOC)
		{
			if (access(HERE_DOC_TMP, F_OK) == 0 && unlink(HERE_DOC_TMP) == -1)
				perror(ERR_UNLINK);
		}
		tok = tok->next;
	}
}

// TOdo: need to close here_doc 
void	close_redirections(t_token *tok)
{
	if (tok->token == INPUT || tok->token == OUTPUT_APPEND || \
			tok->token == OUTPUT_TRUNC)
	{
		if (tok->fd_file > 2 && close(tok->fd_file) == -1)
			perror(ERR_CLOSE);
	}
	else if (tok->token == HERE_DOC)
	{
		if (access(HERE_DOC_TMP, F_OK) == 0 && unlink(HERE_DOC_TMP) == -1)
			perror(ERR_UNLINK);
	}
}
