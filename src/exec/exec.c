/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:00:17 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/28 14:14:45 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "input.h"

static void	exec_token_list(t_token *token, t_global *shell);
static int	check_for_builtins(t_token *token, t_global *shell);

// Todo: protect tcsetattr and tcgetattr with isatty
int	exec_start(t_global *shell)
{
	tcsetattr(STDIN, TCSANOW, &shell->saved_attr);
	set_execution_signals();
	if (setup_all_redirections(shell, shell->token_list) != 1)
		exec_token_list(shell->token_list, shell);
	close_all_redirections(shell->token_list);
	return (0);
}

static void	exec_token_list(t_token *token, t_global *shell)
{
	t_token	*head;

	head = token;
	while (token)
	{
		if (token->token == CMD)
			exec_cmd(token, shell);
		token = token->next;
	}
	token = head;
	while (token)
	{
		if (token->token == CMD)
		{
			if (token->pid > 0 && token->exit_status != COMMAND_NOT_FOUND)
			{
				waitpid(token->pid, &token->exit_status, 0);
				token->exit_status = WEXITSTATUS(token->exit_status);
			}
			g_status = token->exit_status;
		}
		token = token->next;
	}
}

void	exec_cmd(t_token *token, t_global *shell)
{
	if (token->make_a_pipe && pipe(token->pipe_fd) == -1)
		exec_cmd_error(shell, ERR_PIPE);
	if (check_for_builtins(token, shell))
		return ;
	else if (access(token->cmd[0], X_OK) == -1)
	{
		token->exit_status = COMMAND_NOT_FOUND;
		ft_printf_fd(STDERR, "command not found: %s\n", token->cmd[0]);
		return ;
	}
	token->pid = fork();
	if (token->pid == -1)
		exec_cmd_error(shell, ERR_FORK);
	if (token->pid == 0 && exec_child(token, shell->env))
	{
		close_redirections(token);
		exit(EXIT_FAILURE);
	}
	parent_close_pipes(token);
}

static int	check_for_builtins(t_token *token, t_global *shell)
{
	int	is_builtin;

	is_builtin = 0;
	token->exit_status = parse_builtins(token, &is_builtin, shell);
	if (is_builtin)
		parent_close_pipes(token);
	return (is_builtin);
}
