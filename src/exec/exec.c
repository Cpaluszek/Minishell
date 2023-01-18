/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:00:17 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/17 15:11:15 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include "exec.h"
#include "errors.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

// Note: Return int useful ?
// Todo: toggle signals and disable signals
int	exec_start(t_global *shell)
{
	t_block	*blocks;

	blocks = shell->block_list;
	while (blocks)
	{
		exec_token_list(blocks);
		// Todo: check exit status code
		blocks = blocks->next;
	}
	return (0);
}

// Todo: check for maximum amount of pipes
// Todo: protect malloc for pipes
// Note: pipe creation:
	// create pipe when writing needed
	// when reading into pipe, recover previous pipe
int	exec_token_list(t_block *block)
{
	t_token	*tokens;
	int		*pipes_fd;
	int		pipe_index;
	int		is_builtin;
	int		return_val;

	tokens = block->token_list;
	// Todo: create pipes
	while (tokens != NULL)
	{
		if (tokens->token == CMD)
		{
			is_builtin = 0;
			return_val = parse_builtins(tokens, &is_builtin);
			if (!is_builtin)
				return_val = exec_cmd(tokens, pipes_fd, &pipe_index);
			// Todo set return val to $? (global)
		}
		tokens = tokens->next;
	}
	// Todo: close all pipes
	while (waitpid(-1, NULL, 0) > 0)
		;
}

// Todo: protect dup2 + fork + malloc (error message ?)
// Todo: check redirections
	// create a function that checks pipes + redirection and returns fd
int	exec_cmd(t_token *token, int *pipes_fd, int *pipe_index)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		print_perror_exit("fork: ");
	if (pid != 0)
		return (0);
	token->cmd = find_exec(token->str);
	if (token->cmd == NULL)
		return (-1);
	manage_redir_pipes(token, pipes_fd, pipe_index);
	execve(token->cmd[0], token->cmd, NULL);
	ft_free_split(token->cmd);
	exit (0);
}

// Redirection or pipe
// [cmd] [</>] [pipe]
// [</>] [cmd] [pipe]
// Note: if pipe + redir (redir wins ?)
void	manage_redir_pipes(t_token *token, int *pipes_fd, int *pipe_index)
{
	int	input_fd;
	int	output_fd;

	input_fd = STDIN_FILENO;
	output_fd = STDOUT_FILENO;
	if (token->prev)
	{
		if (token->prev->token == PIPE)
			input_fd = pipes_fd[2 * (*pipe_index)];
	}
	if (token->next)
	{
		if (token->next->token == PIPE)
		{
			input_fd = pipes_fd[2 * (*pipe_index) + 1];
			(*pipe_index)++;
		}
	}
	if (token->prev)
	{
		check_redir(token->prev, &input_fd, &output_fd);
		if (token->prev->prev)
			check_redir(token->prev, &input_fd, &output_fd);
	}
	if (token->next)
	{
		check_redir(token->next, &input_fd, &output_fd);
		if (token->next->next)
			check_redir(token->next, &input_fd, &output_fd);
	}

}

void	check_redir(t_token *token, int *input_fd, int *output_fd)
{
	enum e_token type;

	type = token->token;
	if (type == INPUT)
		input_fd = open(token->str, O_RDONLY);
	else if (type == HERE_DOC)
		input_fd = manage_here_doc(token->prev->str);
	else if (type == OUTPUT_APPEND)
		output_fd = open(token->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (type == OUTPUT_TRUNC)
		output_fd = open(token->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
}
