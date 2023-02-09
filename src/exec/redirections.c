/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:39:33 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/09 16:58:48 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "input.h"

void	close_redirs(int fd_in, int fd_out)
{
	if (fd_in > 0 && close(fd_in) == -1)
		perror(ERR_CLOSE);
	if (fd_out > 0 && close(fd_out) == -1)
		perror(ERR_CLOSE);
}

int	setup_input_redir(t_token *tok, t_global *shell, int fd_redir_in)
{
	if (fd_redir_in > 0 && close(fd_redir_in) == -1)
		perror(ERR_CLOSE);
	if (tok->token == INPUT)
		tok->fd_file = open(tok->str, O_RDONLY);
	else
	{
		if (here_doc(shell, tok) != 0)
			{;} //Todo: error
		tok->fd_file = open(HERE_DOC_TMP, O_RDONLY);
	}
	return (tok->fd_file);
}

int	setup_output_redir(t_token *tok, int fd_redir_out)
{
	if (fd_redir_out > 0 && close(fd_redir_out) == -1)
		perror(ERR_CLOSE);
	if (tok->token == OUTPUT_TRUNC)
		tok->fd_file = open(tok->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (tok->token == OUTPUT_APPEND)
		tok->fd_file = open(tok->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (tok->fd_file);
}
