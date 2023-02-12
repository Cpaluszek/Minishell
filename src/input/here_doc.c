/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:06:39 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/12 13:42:51 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "env.h"
#include "input.h"

#define HERE_DOC_PROMPT	"> "

static void	here_doc_child(t_global *shell, t_token *token);
static void	get_here_doc_input(t_global *shell, char *delim, int file);
static void	here_doc_error(t_global *shell, char *str, int file, char *error);

// Todo: not expand dollars in delimiter
// Todo: remove extra /n with ctrl-C
// Todo: check signals management - same as in wait_for_childs ?
int	here_doc(t_global *shell, t_token *token)
{
	int					exit_status;
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sa.sa_sigaction = handle_here_doc_sigquit;
	sigaction(SIGQUIT, &sa, NULL);
	if (pipe(token->pipe_fd) == -1)
		exec_cmd_error(shell, ERR_PIPE, token);
	token->pid = fork();
	if (token->pid == -1)
		error_exit_shell(shell, ERR_FORK);
	if (token->pid == 0)
		here_doc_child(shell, token);
	if (close(token->pipe_fd[1]) == -1)
		perror(ERR_CLOSE);
	waitpid(token->pid, &exit_status, 0);
	token->exit_status = WEXITSTATUS(exit_status);
	g_status = WEXITSTATUS(exit_status);
	set_execution_signals(shell);
	return (token->exit_status);
}

static void	here_doc_child(t_global *shell, t_token *token)
{
	set_here_doc_signals();
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
		if (buff == NULL || ft_strcmp(buff, delim) == 0)
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

static void	here_doc_error(t_global *shell, char *str, int fd, char *error)
{
	ft_free(str);
	if (close(fd) == -1)
		perror(ERR_CLOSE);
	error_exit_shell(shell, error);
}
