/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:06:39 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/12 15:51:46 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "env.h"
#include "input.h"

#define HERE_DOC_PROMPT	"> "

static void	here_doc_child(t_global *shell, t_token *token);
static void	get_here_doc_input(t_global *shell, char *delim, int fd);
static void	here_doc_error(t_global *shell, char *str, int fd, char *error);
static int	check_here_doc_end(char *buff, char *delim);

// Todo: not expand dollars in delimiter
int	here_doc(t_global *shell, t_token *token)
{
	signal(SIGQUIT, SIG_IGN);
	if (pipe(token->pipe_fd) == -1)
		exec_cmd_error(shell, ERR_PIPE, token);
	token->pid = fork();
	if (token->pid == -1)
		error_exit_shell(shell, ERR_FORK);
	if (token->pid == 0)
		here_doc_child(shell, token);
	if (close(token->pipe_fd[1]) == -1)
		perror(ERR_CLOSE);
	waitpid(token->pid, &token->exit_status, 0);
	token->exit_status = WEXITSTATUS(token->exit_status);
	g_status = token->exit_status;
	set_execution_signals(shell);
	return (token->exit_status);
}

static void	here_doc_child(t_global *shell, t_token *token)
{
	set_here_doc_signals(shell);
	if (close(token->pipe_fd[0]) == -1)
		perror(ERR_CLOSE);
	get_here_doc_input(shell, token->str, token->pipe_fd[1]);
	if (close(token->pipe_fd[1]) == -1)
		perror(ERR_CLOSE);
	exit(0);
}

static void	get_here_doc_input(t_global *shell, char *delim, int fd)
{
	char	*buff;
	char	*content;

	content = NULL;
	while (1)
	{
		buff = readline(HERE_DOC_PROMPT);
		if (check_here_doc_end(buff, delim))
			break ;
		buff = check_for_expand(shell, buff);
		buff = ft_strjoin_and_free(buff, "\n");
		if (buff == NULL)
			here_doc_error(shell, content, fd, ERR_MALLOC);
		content = ft_strjoin_and_free(content, buff);
		if (content == NULL)
			here_doc_error(shell, content, fd, ERR_MALLOC);
	}
	ft_free(buff);
	if (content == NULL)
		return ;
	if (write(fd, content, ft_strlen(content)) == -1)
		here_doc_error(shell, content, fd, ERR_WRITE);
	ft_free(content);
}

static int	check_here_doc_end(char *buff, char *delim)
{
	if (buff == NULL || ft_strcmp(buff, delim) == 0)
	{
		if (buff == NULL)
			write(1, "\n", 1);
		return (1);
	}
	return (0);
}

static void	here_doc_error(t_global *shell, char *str, int fd, char *error)
{
	ft_free(str);
	if (close(fd) == -1)
		perror(ERR_CLOSE);
	error_exit_shell(shell, error);
}
