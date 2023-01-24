/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:00:17 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/24 15:16:44 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

// Todo: protect tcsetattr and tcgetattr with isatty
int	exec_start(t_global *shell)
{
	tcsetattr(STDIN, TCSANOW, &shell->saved_attr);
	setup_all_redirections(shell, shell->token_list);
	exec_token_list(shell->token_list, shell);
	close_all_redirections(shell->token_list);
	return (0);
}

int	exec_token_list(t_token *token, t_global *shell)
{
	t_token	*head;

	head = token;
	set_execution_signals();
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
			printf("%s -> %d\n", token->cmd[0], g_status);
		}
		token = token->next;
	}
	return (0);
}

// Note: some builtins need fork to works with pipes
void	exec_cmd(t_token *token, t_global *shell)
{
	int	is_builtin;

	is_builtin = 0;
	token->exit_status = parse_builtins(token, &is_builtin, shell);
	if (is_builtin)
	{
		printf("builtin return = %d\n", token->exit_status);
		return ;
	}
	else if (access(token->cmd[0], X_OK) == -1)
	{
		g_status = COMMAND_NOT_FOUND;
		token->exit_status = COMMAND_NOT_FOUND;
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
