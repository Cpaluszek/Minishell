/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:06:39 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/17 17:20:26 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

char	*get_next_line(int fd);
// NOTE: check argc error ?
// Note: here_doc in a fork to manage CTRL-C
int	main(int argc, char **argv, char **env)
{
	t_global	shell;
	t_token		*token_list;
	// Manage signals
		// Intercept SIGQUIT (^\)
		// Ignore SIGERM SIGHUP, SIGTSTP, SIGTTOU
	// Block control characters printing (^C, ^\) ->tcgetattr & tcsetattr

	// Manage env -> store env in file (unlink at the end)
	// Get PATH from env
	(void) argc;
	(void) argv;
	set_environment(&shell, env);
	while (1)
	{
		reset_commands(&shell);
		shell.path = get_path(&shell, shell.env);
		central_parsing(&shell, PROMPT);
		token_list = shell.token_list;
		while (token_list)
		{
			printf("{ [%s]:[%s], SL(%d)} -> ", token_list->token_str, token_list->str, token_list->space_link);
			token_list = token_list->next;
		}
		// while (token_list)
		// {
		// 	printf("{ [%s]:[", token_list->token_str);
		// 	i = 0;
		// 	while (token_list->cmd[i])
		// 		printf("%s", token_list->cmd[i++]);
		// 	printf("], SL(%d)} -> ", token_list->space_link);
		// 	token_list = token_list->next;
		// }
		printf("\n");
		// Lexically analyze

		// Parse

		// Execute
	}

	return (0);
}

/*
	Function that will get each line read in the standard input.
*/
// char	*get_next_line(int fd)
// {
// 	char	buffer[1001];
// 	char	*line;

// 	ft_bzero(buffer, 1001);
// 	line = ft_calloc(1, sizeof(char));
// 	read(fd, buffer, 1000);
// 	while (!ft_strrchr(buffer, '\n') && ft_strlen(buffer))
// 	{
// 		line = ft_strjoin_free_s1(line, buffer);
// 		ft_bzero(buffer, 1001);
// 		read(STDIN_FILENO, buffer, 1000);
// 	}
// 	line = ft_strjoin_free_s1(line, buffer);
// 	return (line);
// }

