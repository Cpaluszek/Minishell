/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:06:39 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/20 12:10:33 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "exec.h"
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

// char	*get_next_line(int fd);
void	print_command_line(t_token *token_list);
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
	(void) argc;
	(void) argv;
	set_environment(&shell, env);
	while (1)
	{
		reset_commands(&shell);
		shell.path = get_path(&shell, shell.env);
		central_parsing(&shell, PROMPT);
		token_list = shell.token_list;
		print_command_line(token_list);
		exec_start(&shell);
		// printf("\n");
	}
	return (0);
}

// PROBLEME DANS LES FD IN ET OUT, difference de 4 chaque fois dans l'adresse, sinon fonctionne. ATTENTION ane pas commencer
// par des quotes en debut de commande ou juste apres un pipe : risque de SEGFAULT non resolu;

// void	short_test_exec(t_global *shell)
// {
// 	t_token *token;
// 	t_token *first;
// 	// int		status;

// 	first = shell->token_list;
// 	token = first;
// 	while (token)
// 	{
// 		if (token->token <= 1)
// 			token->fd_file = open(token->str, O_RDONLY);
// 		else if (token->token <= 3 && token->token >= 2)
// 			token->fd_file = open(token->str, O_WRONLY | O_TRUNC | O_CREAT, 0000644);
// 		token = token->next;
// 	}
// 	token = first;
// 	while (token)
// 	{
// 		if (token->token == CMD)
// 		{
// 			if (token->make_a_pipe == true)
// 				pipe(token->pipe_fd);
// 			token->pid = fork();
// 			if (token->pid == 0)
// 			{
// 				if (token->fd_input)
// 					dup2(*token->fd_input, STDIN_FILENO);
// 				if (token->fd_output)
// 					dup2(*token->fd_output, STDOUT_FILENO);
// 				if (execve(token->cmd[0], token->cmd, shell->env) == -1)
// 					exit(0);
// 			}
// 		}
// 		wait(NULL);
// 		token = token->next;
// 	}
// 	token = first;
// 	// while (token)
// 	// {
// 	// 	if (token->token == CMD)
// 	// 		waitpid(token->pid, &status, 0);
// 	// 	token = token->next;
// 	// }
// }

void	print_command_line(t_token *token_list)
{
	int	i;
	int	*fd_in;
	int *fd_out;

	printf("\n\n------------COMMAND LINE ------------\n\n");
	while (token_list)
	{
		dprintf(1, "{ [%s]:[", token_list->token_str);
		if (token_list->token == CMD)
		{
			i = 0;
			while (token_list->cmd[i])
				dprintf(1, "%s ", token_list->cmd[i++]);
			fd_in = token_list->fd_input;
			fd_out = token_list->fd_output;
			dprintf(1, "], pipe[%p,%p], fd_in(%p), fd_out(%p)} -> ", &token_list->pipe_fd[0],&token_list->pipe_fd[1], fd_in, fd_out);
		}
		else
		{
			dprintf(1, "%s", token_list->str);
			dprintf(1, "], (%p)} -> ", &token_list->fd_file);
		}
		token_list = token_list->next;
	}
	printf("\n");
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

