/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_signals_handlers.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 12:28:18 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/20 14:09:07 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include <fcntl.h>

/**
 * @brief signal handler: ctrl-C here_doc
 * Stop the here_doc child process and give the prompt back
 * 
 * @param signum signal code
 * @param info additional information about the signal
 * @param context additional information about the signal
 */
void	handle_here_doc_sigint(int signum, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	(void) signum;
	write(1, "^C\n", 3);
	close(5);
	exit(128 + signum);
}
