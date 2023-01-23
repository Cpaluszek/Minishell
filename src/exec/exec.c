/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:00:17 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/23 13:19:33 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "exec.h"

static void	parent_close_pipes(t_token *token);

// Todo: here_doc does not expand $var
int	exec_start(t_global *shell)
{
	tcsetattr(STDIN, TCSANOW, &shell->saved_attr);
	setup_redirections(shell->token_list);
	exec_token_list(shell->token_list, shell);
	return (0);
}

// Todo: child status code
int	exec_token_list(t_token *token, t_global *shell)
{
	while (token)
	{
		if (token->token == CMD)
			exec_cmd(token, shell);
		token = token->next;
	}
	set_execution_signals();
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (0);
}

// Todo: recover builtins exit status
// Todo: protect close
// Note: some builtins need fork to works with pipes
// Note: how to manage command not found ? continue exec line ?
int	exec_cmd(t_token *token, t_global *shell)
{
	int	is_builtin;

	is_builtin = 0;
	g_status = parse_builtins(token, &is_builtin, shell);
	if (is_builtin)
		return (0);
	else if (access(token->cmd[0], X_OK) == -1)
	{
		g_status = COMMAND_NOT_FOUND;
		ft_printf_fd(STDERR, "command not found: %s\n", token->cmd[0]);
		return (0);
	}
	if (token->make_a_pipe)
		pipe(token->pipe_fd);
	token->pid = fork();
	if (token->pid == -1)
		error_exit_exec(shell, ERR_FORK);
	if (token->pid == 0)
		exec_child(token, shell->env);
	parent_close_pipes(token);
	return (0);
}

static void	parent_close_pipes(t_token *token)
{
	if (token->make_a_pipe)
		close(token->pipe_fd[1]);
	if (token->prev && token->prev->make_a_pipe)
		close(token->prev->pipe_fd[0]);
}
