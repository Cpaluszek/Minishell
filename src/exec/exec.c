/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:00:17 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/09 17:02:27 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "input.h"

static void	exec_token_list(t_token *token, t_global *shell);
static void	exec_cmd(t_token *token, t_global *shell);
static void	wait_for_token_list(t_token *token);

// Todo: attention a `./ls | cat -e` qui ne doit executer que le local
// Todo: test max amount of pipes
// Todo: test `rm -rf *`
// Todo: test permissions on redirections
int	exec_start(t_global *shell)
{
	if (isatty(STDIN) && tcsetattr(STDIN, TCSANOW, &shell->saved_attr) == -1)
		perror(ERR_TCSET);
	set_execution_signals();
	exec_token_list(shell->token_list, shell);
	wait_for_token_list(shell->token_list);
	return (0);
}

// Todo: extract functions
static void	exec_token_list(t_token *token, t_global *shell)
{
	t_token	*cmd;
	int		*prev_pipe;
	int		redir_in;
	int		redir_out;
	int		create_half_pipe;

	prev_pipe = NULL;
	create_half_pipe = 0;
	while (token)
	{
		redir_in = 0;
		redir_out = 0;
		cmd = NULL;
		while (token)
		{
			if (token->token <= OUTPUT_APPEND)
			{
				// Todo: check redir errors
				if (token->token <= HERE_DOC)
					redir_in = setup_input_redir(token, shell, redir_in);
				else if (token->token <= OUTPUT_APPEND)
					redir_out = setup_output_redir(token, redir_out);
			}
			else if (token->token == CMD)
			{
				token->fd_input = NULL;
				token->fd_output = NULL;
				token->make_a_pipe = 0;
				cmd = token;
				if (prev_pipe != NULL)
				{
					cmd->fd_input = &prev_pipe[0];
					prev_pipe = NULL;
				}
			}
			else if (token->token == PIPE)
			{
				if (cmd != NULL)
				{
					if (pipe(cmd->pipe_fd) == -1)
					{
						close_redirs(redir_in, redir_out);
						exec_cmd_error(shell, ERR_PIPE, token);
					}
					cmd->fd_output = &cmd->pipe_fd[1];
					cmd->make_a_pipe = 1;
					prev_pipe = cmd->pipe_fd;
				}
				else
					create_half_pipe = 1;
				break ;
			}
			token = token->next;
		}
		if (cmd == NULL)
		{
			if (prev_pipe != NULL && prev_pipe[0] > 2 && close(prev_pipe[0]))
				perror(ERR_CLOSE);
		}
		else
		{
			if (create_half_pipe)
			{
				if (pipe(cmd->pipe_fd) == -1)
				{
					close_redirs(redir_in, redir_out);
					exec_cmd_error(shell, ERR_PIPE, token);
				}
				cmd->fd_input = &cmd->pipe_fd[0];
				if (close(cmd->pipe_fd[1]) == -1)
					perror(ERR_CLOSE);
				cmd->make_a_pipe = 2;
				prev_pipe = cmd->pipe_fd;
				create_half_pipe = 0;
			}
			if (redir_in != 0)
				cmd->fd_input = &redir_in;
			if (redir_out != 0)
				cmd->fd_output = &redir_out;
			exec_cmd(cmd, shell);
		}
		close_redirs(redir_in, redir_out);
		if (token != NULL)
			token = token->next;
	}
}

static void	wait_for_token_list(t_token *token)
{
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

// Todo: too much fork - bash does not exit
static void	exec_cmd(t_token *token, t_global *shell)
{
	if (check_for_builtins(token, shell))
		return ;
	else if (access(token->cmd_path, X_OK) == -1)
	{
		if (ft_strchr(token->cmd_path, '/') != NULL)
			ft_printf_fd(STDERR, "%s: No such file or directory\n", \
				token->cmd[0]);
		else
			ft_printf_fd(STDERR, "command not found: %s\n", token->cmd[0]);
		token->exit_status = COMMAND_NOT_FOUND;
		close_token_pipes(token);
		return ;
	}
	token->pid = fork();
	if (token->pid == -1)
		exec_cmd_error(shell, ERR_FORK, token);
	if (token->pid == 0 && exec_child(token, shell->env))
	{
		close_token_pipes(token);
		exit(EXIT_FAILURE);
	}
	parent_close_pipes(token);
}
