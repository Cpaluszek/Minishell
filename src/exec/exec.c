/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:00:17 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/23 17:35:50 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

static void	parent_close_pipes(t_token *token);

// Todo: here_doc does not expand $var
// Todo: protect tcsetattr and tcgetattr with isatty
int	exec_start(t_global *shell)
{
	tcsetattr(STDIN, TCSANOW, &shell->saved_attr);
	setup_all_redirections(shell->token_list);
	exec_token_list(shell->token_list, shell);
	return (0);
}

// Todo: child status code
int	exec_token_list(t_token *token, t_global *shell)
{
	t_token	*head;

	head = token;
	while (token)
	{
		if (token->token == CMD)
			exec_cmd(token, shell);
		token = token->next;
	}
	set_execution_signals();
	while (waitpid(-1, NULL, 0) > 0)
		;
	close_all_redirections(head);
	return (0);
}

// Todo: recover builtins exit status
// Note: some builtins need fork to works with pipes
void	exec_cmd(t_token *token, t_global *shell)
{
	int	is_builtin;

	is_builtin = 0;
	g_status = parse_builtins(token, &is_builtin, shell);
	if (is_builtin)
		return ;
	else if (access(token->cmd[0], X_OK) == -1)
	{
		g_status = COMMAND_NOT_FOUND;
		ft_printf_fd(STDERR, "command not found: %s\n", token->cmd[0]);
		return ;
	}
	if (token->make_a_pipe && pipe(token->pipe_fd) == -1)
	{
		perror(ERR_PIPE);
		close_all_redirections(shell->token_list);
		error_exit_shell(shell, ERR_FORK);
	}
	token->pid = fork();
	if (token->pid == -1)
	{
		perror(ERR_FORK);
		close_all_redirections(shell->token_list);
		error_exit_shell(shell, ERR_FORK);
	}
	if (token->pid == 0)
	{
		if (exec_child(token, shell->env))
		{
			close_redirections(token);
			exit(EXIT_FAILURE);
		}
	}
	parent_close_pipes(token);
}

static void	parent_close_pipes(t_token *token)
{
	if (token->make_a_pipe)
		close(token->pipe_fd[1]);
	if (token->prev && token->prev->make_a_pipe)
		close(token->prev->pipe_fd[0]);
}
