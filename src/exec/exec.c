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
#include <stdio.h>

int	exec_start(t_global *shell)
{
	setup_redirections(shell->token_list);
	exec_token_list(shell->token_list, shell->env);
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

int	exec_token_list(t_token *token, char **env)
{
	while (token)
	{
		if (token->token == CMD)
			exec_cmd(token, env);
		token = token->next;
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (0);
}

// Todo: recover builtins exit status
// Note: some builtins need fork (echo)
int	exec_cmd(t_token *token, char **env)
{
	int	is_builtin;

	is_builtin = 0;
	parse_builtins(token, &is_builtin);
	if (is_builtin)
	{
		dprintf(STDERR_FILENO, "builtin found - %s\n", token->str);
		return (0);
	}
	else if (access(token->cmd[0], X_OK) == -1)
	{
		perror(token->cmd[0]);
		return (0);
	}
	if (token->make_a_pipe)
		pipe(token->pipe_fd);
	token->pid = fork();
	if (token->pid == -1)
	{
		perror("fork error: ");
		exit (0);
	}
	if (token->pid == 0)
	{
		if (token->fd_input != NULL)
		{
			dup2(*(token->fd_input), STDIN_FILENO);
			dprintf(STDERR_FILENO, "%s: dup(%d, 0)\n",token->str, *(token->fd_input));
			close(*(token->fd_input));
		}
		if (token->fd_output != NULL)
		{
			dup2(*(token->fd_output), STDOUT_FILENO);
			dprintf(STDERR_FILENO, "%s: dup(%d, 1)\n",token->str, *(token->fd_output));
			close(*(token->fd_output));
		}
		execve(token->cmd[0], token->cmd, env);
		exit(0);
	}
	else if (token->make_a_pipe)
		close(token->pipe_fd[1]);
	return (0);
}
