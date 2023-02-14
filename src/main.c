/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:06:39 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/14 15:24:29 by cpalusze         ###   ########.fr       */
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
//TODO : Ambiguous redirect pour des expands pas claires (a = "ls -lr")
//TODO : ajouter un char "msh" devant le display des erreurs pour que ca soit plus classe.
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
	fd = open("block_command.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
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
		// if (token_list)
		// 	print_command_line(token_list);
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
	}
	close(fd);
	return (EXIT_SUCCESS);
}
