/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:00:17 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/18 17:36:48 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "exec.h"
#include <unistd.h>

int	exec_start(t_global *shell)
{
	setup_redirections(shell->token_list);
	exec_cmd(shell->token_list, shell->env);
	return (0);
}

void	setup_redirections(t_token *tok)
{
	while (tok)
	{
		if (tok->token == INPUT)
			tok->fd_file = open(tok->str, O_RDONLY);
		else if (tok->token == OUTPUT_TRUNC)
			tok->fd_file = open(tok->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (tok->token == OUTPUT_APPEND)
			tok->fd_file = open(tok->str, O_RDONLY | O_CREAT | O_APPEND, 0644);
		tok = tok->next;
	}
}

int	exec_cmd(t_token *token, char **env)
{
	while (token)
	{
		if (token->token == CMD)
		{
			if (token->make_a_pipe)
				pipe(token->pipe_fd);
			token->pid = fork();
			if (token->pid == 0)
			{
				if (token->fd_input != NULL)
					dup2(*(token->fd_input), STDIN_FILENO);
				if (token->fd_output != NULL)
					dup2(*(token->fd_output), STDIN_FILENO);
				execve(token->cmd[0], token->cmd, env);
				exit(0);
			}
		}
		wait(NULL);
		token = token->next;
	}
	return (0);
}

// Redirection or pipe
// [cmd] [</>] [pipe]
// [</>] [cmd] [pipe]
// Note: if pipe + redir (redir wins ?)
// void	manage_redir_pipes(t_token *token, int *pipes_fd, int *pipe_index)
// {
// 	int	input_fd;
// 	int	output_fd;

// 	input_fd = STDIN_FILENO;
// 	output_fd = STDOUT_FILENO;
// 	if (token->prev)
// 	{
// 		if (token->prev->token == PIPE)
// 			input_fd = pipes_fd[2 * (*pipe_index)];
// 	}
// 	if (token->next)
// 	{
// 		if (token->next->token == PIPE)
// 		{
// 			input_fd = pipes_fd[2 * (*pipe_index) + 1];
// 			(*pipe_index)++;
// 		}
// 	}
// 	if (token->prev)
// 	{
// 		check_redir(token->prev, &input_fd, &output_fd);
// 		if (token->prev->prev)
// 			check_redir(token->prev, &input_fd, &output_fd);
// 	}
// 	if (token->next)
// 	{
// 		check_redir(token->next, &input_fd, &output_fd);
// 		if (token->next->next)
// 			check_redir(token->next, &input_fd, &output_fd);
// 	}

// }

// void	check_redir(t_token *token, int *input_fd, int *output_fd)
// {
// 	enum e_token type;

// 	type = token->token;
// 	if (type == INPUT)
// 		input_fd = open(token->str, O_RDONLY);
// 	else if (type == HERE_DOC)
// 		input_fd = manage_here_doc(token->prev->str);
// 	else if (type == OUTPUT_APPEND)
// 		output_fd = open(token->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
// 	else if (type == OUTPUT_TRUNC)
// 		output_fd = open(token->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
// }
