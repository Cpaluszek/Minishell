/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:06:39 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/21 08:30:37 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "exec.h"
#include "input.h"

int		g_status;

// Todo : check protect fork and pipe in exec_block_list
// Todo: here_doc sometimes fail with `<< a cat` -> order matter
// Todo: check headers and remove TEIKI
// Todo: unset du PATH -> /bin/ls should work
// Todo : do not export charset with non alhanumeri character sur as {,}, ...
// Todo : do not expand wildcard in export function.
// Todo : merge quote with wildcards correctly.
// Todo: remove all todos
int	main(int argc, char **argv, char **env)
{
	t_global		shell;

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
		if (shell.command_line == COMPLETED)
		{
			set_execution_signals(&shell);
			exec_block_list(&shell, shell.block_list);
		}
		else if (shell.command_line == SYNTAX_ERROR)
			g_status = 2;
	}
	return (EXIT_SUCCESS);
}
