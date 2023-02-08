/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:00:17 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/08 15:58:19 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "input.h"

static void	exec_token_list(t_token *token, t_global *shell);
static void	exec_cmd(t_token *token, t_global *shell);

// Todo: attention a `./ls | cat -e` qui ne doit executer que le local
// Todo: test max amount of pipes
// Todo: test `rm -rf *`
// Todo: test permissions on redirections
// EN REFLEXION :
// ->  je pense qu'on a pas choisi la meilleure option pour l'enchainement des ouvertures des INPUT /OUT PUTS et l'exec des commandes
// il vaudrait mieux ouvrir les directions pour une seule commande et les fermer apres l'execution de la commande
int	exec_start(t_global *shell)
{
	if (isatty(STDIN) && tcsetattr(STDIN, TCSANOW, &shell->saved_attr) == -1)
		perror(ERR_TCSET);
	set_execution_signals();
	// if (setup_all_redirections(shell, shell->token_list) != 1)
	exec_token_list(shell->token_list, shell);
	// close_all_redirections(shell->token_list);
	return (0);
}

static void	exec_token_list(t_token *token, t_global *shell)
{
	t_token	*head;
	int		*prev_pipe_fd_in;
	int		fd_redir_in;
	int		fd_redir_out;
	t_token	*cmd;

	head = token;
	prev_pipe_fd_in = NULL;
	while (token)
	{
		fd_redir_in = 0;
		fd_redir_out = 0;
		cmd = NULL;
		while (token && token->token != PIPE)
		{
			// Open redir
			if (token->token <= HERE_DOC)
			{
				if (fd_redir_in > 0 && close(fd_redir_in) == -1)
					perror(ERR_CLOSE);
				if (token->token == INPUT)
					token->fd_file = open(token->str, O_RDONLY);
				else
				{
					if (here_doc(shell, token) != 0)
						{;} //Todo: errror
					token->fd_file = open(HERE_DOC_TMP, O_RDONLY);
				}
				dprintf(STDERR, "Open redir_in = %d\n", fd_redir_in);
				fd_redir_in = token->fd_file;
			}
			else if (token->token <= OUTPUT_APPEND)
			{
				if (fd_redir_out > 0 && close(fd_redir_out) == -1)
					perror(ERR_CLOSE);
				if (token->token == OUTPUT_TRUNC)
					token->fd_file = open(token->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				else if (token->token == OUTPUT_APPEND)
					token->fd_file = open(token->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
				fd_redir_out = token->fd_file;
				dprintf(STDERR, "Open redir_out = %d\n", fd_redir_out);
			}
			else if (token->token == CMD)
				cmd = token;
			token = token->next;
		}
		if (cmd == NULL)
		{
			// No cmd - close pipe
			dprintf(STDERR, "cmd = NULL -> close %p = %d\n", prev_pipe_fd_in, *prev_pipe_fd_in);
			if (prev_pipe_fd_in != NULL && close(*prev_pipe_fd_in) == -1)
				perror(ERR_CLOSE);
			prev_pipe_fd_in = NULL;
			// Todo: close redir too
			if (fd_redir_in > 0 && close(fd_redir_in) == -1)
				perror(ERR_CLOSE);
			if (fd_redir_out > 0 && close(fd_redir_out) == -1)
				perror(ERR_CLOSE);
		}
		else
		{
			if (prev_pipe_fd_in != NULL && cmd->fd_input != prev_pipe_fd_in)
				if (close(*prev_pipe_fd_in) == -1)
					perror(ERR_CLOSE);
			// Create the pipe
			if (cmd->make_a_pipe)
			{
				if ((cmd->prev != NULL && cmd->prev->token == PIPE) || \
					(cmd->next != NULL && cmd->next->token == PIPE))
				{
					if (pipe(cmd->pipe_fd) == -1)
						exec_cmd_error(shell, ERR_PIPE, token);
					prev_pipe_fd_in = &cmd->pipe_fd[0];
					dprintf(STDERR, "[%s] creating pipe: (%p)[%d;%d]\n", cmd->str, cmd->pipe_fd, cmd->pipe_fd[0], cmd->pipe_fd[1]);
				}
			}
			exec_cmd(cmd, shell);
			// Close redir after exec
			if (fd_redir_in > 0 && close(fd_redir_in) == -1)
				perror(ERR_CLOSE);
			if (fd_redir_out > 0 && close(fd_redir_out) == -1)
				perror(ERR_CLOSE);
		}
		if (token != NULL)
			token = token->next;
	}
	// Note: use block list to get back head of token_list
	token = head;
	// Wait for end of execution
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
		dprintf(STDERR, "child exec fail\n");
		close_token_pipes(token);
		exit(EXIT_FAILURE);
	}
	parent_close_pipes(token);
}
