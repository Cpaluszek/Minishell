/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:06:39 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/17 14:05:16 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "exec.h"
#include "input.h"

void	print_command_line2(t_token *token_list, int fd);
int		g_status;

int	main(int argc, char **argv, char **env)
{
	t_global		shell;
	t_token			*token_list;
	int				fd;

	// if (!isatty(STDIN))
	// {
	// 	printf("Minishell cannot run with a pipe\n");
	// 	close(STDIN);
	// 	close(STDOUT);
	// 	return (0);
	// }
	(void) argc;
	(void) argv;
	(void)token_list;
	g_status = EXIT_SUCCESS;
	init_shell_attr(&shell);
	set_environment(&shell, env);
	fd = open("block_command.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		reset_commands(&shell);
		shell.path = get_path(&shell, shell.env);
		set_interactive_signals(&shell);
		if (g_status == 0)
			central_parsing(&shell, PROMPT);
		else
			central_parsing(&shell, PROMPT_ERR);
		if (shell.block_list)
		{
			dprintf(fd, "\n\nINPUT : %s\n\n", shell.input_completed);
			print_block(shell.block_list, fd);
		}
		else
			dprintf(1, "NOBLOCK\n");
		if (shell.command_line == COMPLETED)
		{
			set_execution_signals(&shell);
			exec_block(&shell, shell.block_list);
		}
		else if (shell.command_line == SYNTAX_ERROR)
			g_status = 258;
	}
	return (EXIT_SUCCESS);
}
