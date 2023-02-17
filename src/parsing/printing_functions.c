/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:01:09 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/17 11:24:13 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	print_command_line2(t_token *token_list, int fd);

void	print_command_line(t_token *token_list)
{
	int	i;
	// int	*fd_in;
	// int	*fd_out;

	printf("\n\n------------COMMAND LINE ------------\n\n");
	while (token_list)
	{
		dprintf(1, "{");
		// dprintf(1, "[%p]", token_list);
		dprintf(1, "[%s]:[", token_list->token_str);
		if (token_list->token == CMD)
		{
			if (!token_list->cmd)
				dprintf(1, "%s(str) %d", token_list->str, token_list->ambiguous_redirect);
			else
			{
				i = 0;
				while (token_list->cmd[i])
					dprintf(1, "{%s }", token_list->cmd[i++]);
				// fd_in = token_list->fd_input;
				// fd_out = token_list->fd_output;
			}
			// dprintf(1, "], pipe[%p,%p], fd_in(%p), fd_out(%p)} -> ", &token_list->pipe_fd[0],&token_list->pipe_fd[1], fd_in, fd_out);
			dprintf(1, "][SL:%d", token_list->space_link);
			dprintf(1, "]} -> ");
		}
		else
		{
			dprintf(1, "%s(%d), SL : %d", token_list->str,token_list->token, token_list->space_link);
			// dprintf(1, "pipe[%p,%p]} -> ", &token_list->pipe_fd[0], &token_list->pipe_fd[1]);
			// dprintf(1, "], (%p)} -> ", &token_list->fd_file);
			dprintf(1, "]} -> ");
		}
		token_list = token_list->next;
	}
	printf("\n");
}

void	print_block(t_block *block, int fd)
{
	int	i;

	dprintf(fd, "\n\n\n");
	i = block->block_level;
	while (i)
	{
		dprintf(fd, "|\t\t\t");
		i--;
	}
	dprintf(fd, "----- NEW BLOCK ----- \n\n");
	if (block->token_list)
	{
		i = block->block_level;
		while (i)
		{
			dprintf(fd, "|\t\t\t");
			i--;
		}
		dprintf(fd, "Block token list : ");
		print_command_line2(block->token_list, fd);
	}
	if (block->redirection_token_list)
	{
		i = block->block_level;
		while (i)
		{
			dprintf(fd, "|\t\t\t");
			i--;
		}
		dprintf(fd, "Block redirection : ");
		print_command_line2(block->redirection_token_list, fd);
	}
	i = block->block_level;
	while (i)
	{
		dprintf(fd, "|\t\t\t");
		i--;
	}
	if (block->logical_link == AND_LINK)
		dprintf(fd, "&&");
	else if (block->logical_link == OR_LINK)
		dprintf(fd, "||");
	else if (block->logical_link == PIPE_LINK)
		dprintf(fd, "|");
	else if (block->logical_link == NO_LINK)
		dprintf(fd, "NO LINK");
	if (block->sub_block)
		print_block(block->sub_block, fd);
	if (block->next)
		print_block(block->next, fd);
}

static void	print_command_line2(t_token *token_list, int fd)
{
	int	i;
	// int	*fd_in;
	// int	*fd_out;

	while (token_list)
	{
		// dprintf(fd, "{");
		// dprintf(fd, "[%p]", token_list);
		if (token_list->token != CMD)
			dprintf(fd, " %s", token_list->token_str);
		if (token_list->token == CMD)
		{
			if (!token_list->cmd)
				dprintf(fd, "%s(str)", token_list->str);
			else
			{
				i = 0;
				while (token_list->cmd[i])
					dprintf(fd, "%s ", token_list->cmd[i++]);
				// fd_in = token_list->fd_input;
				// fd_out = token_list->fd_output;
			}
			// dprintf(fd, "], pipe[%p,%p], fd_in(%p), fd_out(%p)} -> ", &token_list->pipe_fd[0],&token_list->pipe_fd[1], fd_in, fd_out);
			dprintf(fd, " -> ");
		}
		else
		{
			if (token_list->token <= OUTPUT_APPEND)
				dprintf(fd, "%s", token_list->str);
			// dprintf(fd, "], (%p)} -> ", &token_list->fd_file);
			dprintf(fd, " -> ");
		}
		token_list = token_list->next;
	}
	dprintf(fd, "\n");
}
