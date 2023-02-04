/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:06:39 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/30 13:28:23 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "exec.h"
#include "input.h"

void	print_command_line(t_token *token_list);

// NOTE: test
// TODO: test
// Todo: parsing need to update g_status in case of parsing error ?
int	main(int argc, char **argv, char **env)
{
	t_global		shell;
	t_token			*token_list;

	(void) argc;
	(void) argv;
	g_status = EXIT_SUCCESS;
	init_shell_attr(&shell);
	set_environment(&shell, env);
	while (1)
	{
		reset_commands(&shell);
		shell.path = get_path(&shell, shell.env);
		set_interactive_signals(&shell);
		if (g_status == 0)
			central_parsing(&shell, PROMPT);
		else
			central_parsing(&shell, PROMPT_ERR);
		token_list = shell.token_list;
		print_command_line(token_list);
		exec_start(&shell);
	}
	return (EXIT_SUCCESS);
}

void	print_command_line(t_token *token_list)
{
	int	i;
	int	*fd_in;
	int	*fd_out;

	printf("\n\n------------COMMAND LINE ------------\n\n");
	while (token_list)
	{
		dprintf(1, "{[%s]:[", token_list->token_str);
		if (token_list->token == CMD)
		{
			if (!token_list->cmd)
				dprintf(1, "%s(str)", token_list->str);
			else
			{
				i = 0;
				while (token_list->cmd[i])
					dprintf(1, "%s ", token_list->cmd[i++]);
				fd_in = token_list->fd_input;
				fd_out = token_list->fd_output;
			}
			// dprintf(1, "], pipe[%p,%p], fd_in(%p), fd_out(%p)} -> ", &token_list->pipe_fd[0],&token_list->pipe_fd[1], fd_in, fd_out);
			dprintf(1, "]} -> ");
		}
		else
		{
			dprintf(1, "%s", token_list->str);
			// dprintf(1, "], (%p)} -> ", &token_list->fd_file);
			dprintf(1, "]} -> ");
		}
		token_list = token_list->next;
	}
	printf("\n");
}
