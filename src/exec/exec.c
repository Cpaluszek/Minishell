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
		exec_child(token, env);
	else
	{
		if (token->make_a_pipe)
			close(token->pipe_fd[1]);
		if (token->prev && token->prev->make_a_pipe)
			close(token->prev->pipe_fd[0]);
	}
	return (0);
}
