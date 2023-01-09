/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:06:39 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/09 16:35:26 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// NOTE: check argc error ?
int	main(int argc, char **argv, char **env)
{
	// Manage signals
		// Intercept SIGQUIT (^\)
		// Ignore SIGERM SIGHUP, SIGTSTP, SIGTTOU
	// Block control characters printing (^C, ^\) ->tcgetattr & tcsetattr

	// Manage env -> store env in file (unlink at the end)
	// Get PATH from env


	// While 
		// Set the prompt
		// read input

		// Lexically analyze

		// Parse

		// Execute
	return (0);
}
