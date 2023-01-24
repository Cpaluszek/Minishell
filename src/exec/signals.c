/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:39:28 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/24 15:24:16 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

// Note make a header for signals / Input management ?
void	init_shell_attr(t_global *shell)
{
	tcgetattr(STDIN_FILENO, &shell->saved_attr);
	tcgetattr(STDIN_FILENO, &shell->custom_attr);
	shell->custom_attr.c_lflag &= ECHO;
}

// Update interactive mode signals
void	set_interactive_signals(t_global *shell)
{
	struct sigaction	sa;

	tcsetattr(STDIN, TCSAFLUSH, &shell->custom_attr);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	sa.sa_sigaction = handle_interactive_sigquit;
	sigaction(SIGQUIT, &sa, NULL);
	sa.sa_sigaction = handle_abort_input;
	sigaction(SIGINT, &sa, NULL);
}

// Note: in execution mode ctrl-D with bash will close the shell after execution
void	set_execution_signals(void)
{
	struct sigaction	sa;

	dprintf(STDERR, "set execution signals\n");
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	sa.sa_sigaction = handle_execution_sigint;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_sigaction = handle_execution_sigquit;
	sigaction(SIGQUIT, &sa, NULL);
}
