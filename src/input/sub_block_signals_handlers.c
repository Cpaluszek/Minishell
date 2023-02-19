/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_block_signals_handlers.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 00:46:31 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/19 01:00:03 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief signal handler: ctrl-C execution mode
 * Kill the running process and give the prompt back
 * 
 * @param signum signal code
 * @param info additional information about the signal
 * @param context additional information about the signal
 */
void	handle_execution_sub_block_sigint(int signum, siginfo_t \
	*info, void *context)
{
	(void) info;
	(void) context;
	g_status = 128 + signum;
}

/**
 * @brief signal handler: ctrl-\ execution mode
 * Kill the running  process and give the prompt back
 * 
 * @param signum signal code
 * @param info additional information about the signal
 * @param context additional information about the signal
 */
void	handle_execution_sub_block_sigquit(int signum, siginfo_t \
	*info, void *context)
{
	(void) info;
	(void) context;
	g_status = 128 + signum;
}
