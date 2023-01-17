/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:06:39 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/16 16:53:44 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "exec.h"
#include "token_list_functions.h"

static void	debug_token_list(t_token *token_list);
// NOTE: check argc error ?
// Note: here_doc in a fork to manage CTRL-C
int	main(int argc, char **argv, char **env)
{
	t_global	shell;
	char		*input;
	t_token		*token_list;
	// Manage signals
		// Intercept SIGQUIT (^\)
		// Ignore SIGERM SIGHUP, SIGTSTP, SIGTTOU
	// Block control characters printing (^C, ^\) ->tcgetattr & tcsetattr

	// Manage env -> store env in chained list
	// Get PATH from env
	(void) argc;
	(void) argv;
	(void) env;
	while (42)
	{
		input = readline(PROMPT);
		if (input == NULL || ft_strlen(input) == 0)
			continue ;
		add_history(input);
		token_list = central_parsing(input);
		free(input);
		input = NULL;
		exec_start(token_list);
		debug_token_list(token_list);
		// while (token_list->prev)
			// token_list = token_list->prev;
		ft_lstclear_token(&token_list);
	}
	return (0);
}

static void	debug_token_list(t_token *token_list)
{
	while (token_list)
	{
		printf("{ [%s]:[%s], SL(%d)} -> ", token_list->token_str, token_list->str, token_list->space_link);
		token_list = token_list->next;
	}
	printf("\n");
}
