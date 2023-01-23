/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:10:50 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/23 13:28:52 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <readline/readline.h>

/**
 * @brief signal handler: ctrl-\ interactive mode
 * Does nothing.
 * @param signum signal code
 * @param info additional information about the signal
 * @param context additional information about the signal
 */
void	handle_interactive_sigquit(int signum, siginfo_t *info, void *context)
{
	(void) signum;
	(void) info;
	(void) context;
	rl_redisplay();
}

/**
 * @brief signal handler: ctrl-C interactive mode
 * Clear the current line, and show a new prompt
 * 
 * @param signum signal code
 * @param info additional information about the signal
 * @param context additional information about the signal
 */
void	handle_abort_input(int signum, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	g_status = 128 + signum;
}

/**
 * @brief signal handler: ctrl-C execution mode
 * Kill the running process and give the prompt back
 * 
 * @param signum signal code
 * @param info additional information about the signal
 * @param context additional information about the signal
 */
void	handle_execution_sigint(int signum, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	write(1, "\n", 1);
	g_status = 128 + signum;
}

/**
 * @brief signal handler: ctrl-\ execution mode
 * Kill the running process and give the prompt back
 * 
 * @param signum signal code
 * @param info additional information about the signal
 * @param context additional information about the signal
 */
void	handle_execution_sigquit(int signum, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	printf("Quit: %d\n", signum);
	g_status = 128 + signum;
}