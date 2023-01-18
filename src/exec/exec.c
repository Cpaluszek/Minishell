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

int	exec_cmd(t_token *token, char **env)
{
	int	is_builtin;
	int	err;

	err = 0;
	is_builtin = 0;
	err = parse_builtins(token, &is_builtin);
	(void) err;
	if (is_builtin)
	{
		dprintf(STDERR_FILENO, "builtin found - %s\n", token->str);
		return (err);
	}
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
	return (0);
}
