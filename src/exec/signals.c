/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:39:28 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/23 11:38:56 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "structs.h"
#include <readline/readline.h>

// Todo: switch to sigaction instead of signal
// Note make a header for signals / Input management ?
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
	signal(SIGINT, handle_abort_input);
	signal(SIGQUIT, handle_sigquit);
}

/**
 * @brief signal handler: ctrl-D interactive mode
 * 
 * @param sign signal code
 */
void	handle_sigquit(int sign)
{
	(void) sign;
	rl_redisplay();
}

/**
 * @brief signal handler: ctrl-C interactive mode
 * 
 * @param sign signal code
 */
void	handle_abort_input(int sign)
{
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	g_status = 128 + sign;
}
