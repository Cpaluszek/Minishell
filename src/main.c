/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:06:39 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/15 23:36:51 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

char	*get_next_line(int fd);
// NOTE: check argc error ?
int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_token	*token_list;
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
		input = get_next_line(STDIN_FILENO);
		if (input == NULL || ft_strlen(input) == 0)
			continue ;
		token_list = central_parsing(input);
		while (token_list)
		{
			printf("{ [%s]:[%s], SL(%d)} -> ", token_list->token_str, token_list->str, token_list->space_link);
			token_list = token_list->next;
		}
		printf("\n");
		printf("%ld %s\n", ft_strlen(input), input);
		// add_history(input);
		// Lexically analyze

		// Parse

		// Execute
	}

	return (0);
}

/*
	Function that will get each line read in the standard input.
*/
char	*get_next_line(int fd)
{
	char	buffer[1001];
	char	*line;

	ft_bzero(buffer, 1001);
	line = ft_calloc(1, sizeof(char));
	read(fd, buffer, 1000);
	while (!ft_strrchr(buffer, '\n') && ft_strlen(buffer))
	{
		line = ft_strjoin_free_s1(line, buffer);
		ft_bzero(buffer, 1001);
		read(STDIN_FILENO, buffer, 1000);
	}
	line = ft_strjoin_free_s1(line, buffer);
	return (line);
}
