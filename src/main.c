/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:06:39 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/08 10:56:35 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "exec.h"
#include "input.h"

void	print_command_line(t_token *token_list);
void	print_block(t_block *block, int fd);
void	print_command_line2(t_token *token_list, int fd);
int		g_status;

// Todo: parsing need to update g_status in case of parsing error ?
// TODO: env - i : le "_=./minishell" : difference entre absh et minishell
//TODO : Ambiguous redirect pour des expands pas claires (a = "ls -lr")
//TODO : ajouter un char "msh" devant le display des erreurs pour que ca soit plus classe.
//TODO env - i : le "_=./minishell" : difference entre absh et minishell
int	main(int argc, char **argv, char **env)
{
	t_global		shell;
	t_token			*token_list;
	int				fd;

	(void) argc;
	(void) argv;
	(void)token_list;
	g_status = EXIT_SUCCESS;
	init_shell_attr(&shell);
	set_environment(&shell, env);
	while (1)
	{
		fd = open("block_command.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
		reset_commands(&shell);
		shell.path = get_path(&shell, shell.env);
		set_interactive_signals(&shell);
		if (g_status == 0)
			central_parsing(&shell, PROMPT);
		else
			central_parsing(&shell, PROMPT_ERR);
		token_list = shell.token_list;
		// if (token_list)
		// 	print_command_line(token_list);
		if (shell.block_list)
		{
			dprintf(fd, "\n\nINPUT : %s\n\n", shell.input_completed);
			print_block(shell.block_list, fd);
		}
		else
			dprintf(1, "NOBLOCK\n");
		// if (shell.command_line == COMPLETED)
		// 	exec_start(&shell);
	}
	return (EXIT_SUCCESS);
}

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
			// dprintf(1, "], pipe[%p,%p], fd_in(%p), fd_out(%p) mk_pip(%d)} -> ", &token_list->pipe_fd[0],&token_list->pipe_fd[1], fd_in, fd_out, token_list->make_a_pipe);
			dprintf(1, "]} -> ");
		}
		else
		{
			dprintf(1, "%s, %d", token_list->str, token_list->ambiguous_redirect);
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
		dprintf(fd, "\t\t\t");
		i--;
	}
	dprintf(fd, "----- NEW BLOCK ----- \n\n");
	if (block->token_list)
	{
		i = block->block_level;
		while (i)
		{
			dprintf(fd, "\t\t\t");
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
			dprintf(fd, "\t\t\t");
			i--;
		}
		dprintf(fd, "Block redirection : ");
		print_command_line2(block->redirection_token_list, fd);
	}
	if (block->sub_block)
		print_block(block->sub_block, fd);
	if (block->next)
		print_block(block->next, fd);
}

void	print_command_line2(t_token *token_list, int fd)
{
	int	i;
	// int	*fd_in;
	// int	*fd_out;

	while (token_list)
	{
		dprintf(fd, "{");
		// dprintf(fd, "[%p]", token_list);
		dprintf(fd, "[%s]:[", token_list->token_str);
		if (token_list->token == CMD)
		{
			if (!token_list->cmd)
				dprintf(fd, "%s(str) %d", token_list->str, token_list->ambiguous_redirect);
			else
			{
				i = 0;
				while (token_list->cmd[i])
					dprintf(fd, "{%s }", token_list->cmd[i++]);
				// fd_in = token_list->fd_input;
				// fd_out = token_list->fd_output;
			}
			// dprintf(fd, "], pipe[%p,%p], fd_in(%p), fd_out(%p) mk_pip(%d)} -> ", &token_list->pipe_fd[0],&token_list->pipe_fd[1], fd_in, fd_out, token_list->make_a_pipe);
			dprintf(fd, "]} -> ");
		}
		else
		{
			dprintf(fd, "%s, %d", token_list->str, token_list->ambiguous_redirect);
			// dprintf(fd, "], (%p)} -> ", &token_list->fd_file);
			dprintf(fd, "]} -> ");
		}
		token_list = token_list->next;
	}
	dprintf(fd, "\n");
}