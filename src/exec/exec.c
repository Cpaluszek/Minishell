/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:00:17 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/14 11:46:40 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

int	exec_start(s_block **block)
{
	// Foreach block
	while (*block != NULL)
	{
		// Execute token list

		// Check exit status
			// Execute next one depending on link type and exit status
		block = block->next;
	}
	// toggle signals
	// disable signals
}

// For pipes: use minimal amount of pipes
// create pipe in child then close it ASAP
int	exec_block(s_block **block)
{
	// Foreach token
	while (block->token_list)
	{
		// If cmd or builtins
			// Check for redirections
				// Input - Output
			// Exec cmd + manage signals
			// Get exit status code
		block->token_list = block->token_list->next;
	}
	// Set block exit status
}