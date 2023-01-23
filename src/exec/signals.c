/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:39:28 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/23 11:15:11 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "structs.h"
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>

// Note make a header for signals / Input management ?
// Interactive mode - ctrl-D
void	init_shell_attr(t_global *shell)
{
	tcgetattr(STDIN_FILENO, &shell->saved_attr);
	tcgetattr(STDIN_FILENO, &shell->custom_attr);
	shell->custom_attr.c_lflag &= ECHO;
}

// Update interactive mode signals
// Todo: replace param with void
void	set_interactive_signals(t_global *shell)
{
	tcsetattr(STDIN, TCSAFLUSH, &shell->custom_attr);
	dprintf(STDERR_FILENO, "set interactive signals\n");
	signal(SIGINT, handle_abort_input);
	signal(SIGQUIT, handle_sigquit);
}

void	handle_sigquit(int sign)
{
	(void) sign;
	rl_redisplay();
}

// Interactive mode - ctrl-C
void	handle_abort_input(int sign)
{
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	g_status = 128 + sign;
}

void	set_exec_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	printf("set exec signals\n");
	signal(SIGINT, handle_exec_signals);
	perror("Signal error");
	signal(SIGQUIT, handle_exec_signals);
	perror("Signal error");
	printf("done setting up exec signals\n");
}

void	handle_exec_signals(int sign)
{
	dprintf(STDERR_FILENO, "handle exec sign: %d\n", sign);
	g_status = 128 + sign;
}
