/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:39:28 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/12 15:46:06 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "input.h"
#include "errors.h"

void	init_shell_attr(t_global *shell)
{
	if (tcgetattr(STDIN, &shell->saved_attr) == -1)
		perror(ERR_TCGET);
	if (tcgetattr(STDIN, &shell->custom_attr) == -1)
		perror(ERR_TCGET);
	shell->custom_attr.c_lflag &= ECHO;
}

void	set_interactive_signals(t_global *shell)
{
	struct sigaction	sa;

	if (isatty(STDIN) && tcsetattr(STDIN, TCSAFLUSH, &shell->custom_attr) == -1)
		perror(ERR_TCSET);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	sa.sa_sigaction = handle_interactive_sigquit;
	sigaction(SIGQUIT, &sa, NULL);
	sa.sa_sigaction = handle_abort_input;
	sigaction(SIGINT, &sa, NULL);
}

void	set_execution_signals(t_global *shell)
{
	struct sigaction	sa;

	if (isatty(STDIN) && tcsetattr(STDIN, TCSANOW, &shell->saved_attr) == -1)
		perror(ERR_TCSET);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	sa.sa_sigaction = handle_execution_sigint;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_sigaction = handle_execution_sigquit;
	sigaction(SIGQUIT, &sa, NULL);
}


// Todo: test to use saved_attr
void	set_here_doc_signals(void)
{
	struct sigaction	sa;
	struct termios		attr;

	if (tcgetattr(STDIN, &attr) == -1)
		perror(ERR_TCGET);
	else
	{
		attr.c_lflag &= ECHO;
		if (isatty(STDIN) && tcsetattr(STDIN, TCSANOW, &attr) == -1)
			perror(ERR_TCSET);
	}
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	signal(SIGINT, SIG_DFL);
	sa.sa_sigaction = handle_here_doc_sigint;
	sigaction(SIGINT, &sa, NULL);
}
