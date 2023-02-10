/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:06:39 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/10 17:38:32 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "env.h"
#include "input.h"

#define HERE_DOC_PROMPT	"> "

static void	here_doc_child(t_global *shell, char *delim);
static void	get_here_doc_input(t_global *shell, char *delim, int file);
static void	here_doc_write_error(t_global *shell, char *delim, int file);

// Note: how to manage here_doc file error ?
// Note: not expand dollars in delimiter
// Todo: remove extra /n with ctrl-C
// Todo: multiple here_doc with diff cmds will not work
int	here_doc(t_global *shell, t_token *token)
{
	int					exit_status;
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sa.sa_sigaction = handle_here_doc_sigquit;
	sigaction(SIGQUIT, &sa, NULL);
	token->pid = fork();
	if (token->pid == -1)
		error_exit_shell(shell, ERR_FORK);
	if (token->pid == 0)
		here_doc_child(shell, token->str);
	waitpid(token->pid, &exit_status, 0);
	token->exit_status = WEXITSTATUS(exit_status);
	g_status = WEXITSTATUS(exit_status);
	if (isatty(STDIN) && tcsetattr(STDIN, TCSANOW, &shell->saved_attr) == -1)
		perror(ERR_TCSET);
	set_execution_signals();
	return (token->exit_status);
}

static void	here_doc_child(t_global *shell, char *delim)
{
	int		file;

	set_here_doc_signals();
	file = open(HERE_DOC_TMP, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (file == -1)
		perror(ERR_HERE_DOC_FILE);
	get_here_doc_input(shell, delim, file);
	if (close(file) == -1)
		perror(ERR_CLOSE);
	exit(0);
}

static void	get_here_doc_input(t_global *shell, char *delim, int fd)
{
	char	*buff;

	while (1)
	{
		buff = readline(HERE_DOC_PROMPT);
		if (buff == NULL || ft_strcmp(buff, delim) == 0)
			break ;
		buff = check_for_expand(shell, buff);
		if (write(fd, buff, ft_strlen(buff)) == -1 || write(fd, "\n", 1) == -1)
		{
			perror(ERR_WRITE);
			ft_free(buff);
			here_doc_write_error(shell, delim, fd);
		}
		ft_free(buff);
	}
	ft_free(buff);
}

static void	here_doc_write_error(t_global *shell, char *delim, int file)
{
	ft_free(delim);
	if (close(file) == -1)
		perror(ERR_CLOSE);
	error_exit_shell(shell, ERR_WRITE);
}
