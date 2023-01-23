/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:39:33 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/23 14:49:09 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

void	setup_all_redirections(t_token *tok)
{
	while (tok)
	{
		if (tok->token == INPUT)
			tok->fd_file = open(tok->str, O_RDONLY);
		else if (tok->token == OUTPUT_TRUNC)
			tok->fd_file = open(tok->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (tok->token == OUTPUT_APPEND)
			tok->fd_file = open(tok->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		tok = tok->next;
	}
}

void	close_all_redirections(t_token *tok)
{
	while (tok)
	{
		if (tok->token == INPUT || tok->token == OUTPUT_APPEND || \
			tok->token == OUTPUT_TRUNC)
			close(tok->fd_file);
		tok = tok->next;
	}
}

void	close_redirections(t_token *tok)
{
	if (tok->token == INPUT || tok->token == OUTPUT_APPEND || \
			tok->token == OUTPUT_TRUNC)
		close(tok->fd_file);
}
