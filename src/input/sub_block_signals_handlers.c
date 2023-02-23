/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_block_signals_handlers.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:05:45 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/23 13:22:35 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Kill the running  process and give the prompt back
 * without any end of line
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
 * @brief Kill the running  process and give the prompt back
 * without any end of line
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
