/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:06:39 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/14 10:11:38 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// NOTE: check argc error ?
// Note: here_doc in a fork to manage CTRL-C
int	main(int argc, char **argv, char **env)
{
	char	*input;
	// Manage signals
		// Intercept SIGQUIT (^\)
		// Ignore SIGERM SIGHUP, SIGTSTP, SIGTTOU
	// Block control characters printing (^C, ^\) ->tcgetattr & tcsetattr

	// Manage env -> store env in file (unlink at the end)
	// Get PATH from env
	(void) argc;
	(void) argv;
	(void) env;
	while (1)
	{
		// Set the prompt & read input
		input = readline(PROMPT);
		if (input == NULL || ft_strlen(input) == 0)
			continue ;
		printf("%ld %s\n", ft_strlen(input), input);
		add_history(input);
		// Lexically analyze

		// Parse

		// Execute
	}

	return (0);
}
