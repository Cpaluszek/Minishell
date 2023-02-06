/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:00:17 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/02 15:07:06 by Teiki            ###   ########.fr       */
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
// VOIR MEME on pourrait executer les ouvertures / fermetures uniquement dans le processus enfant pour ne pas avoir a le fermer dans le parent.
//-> fausse bonne idee en fait je pense ><
int	exec_start(t_global *shell)
{
	if (isatty(STDIN) && tcsetattr(STDIN, TCSANOW, &shell->saved_attr) == -1)
		perror(ERR_TCSET);
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

// Todo: too much fork - bash does not exit
static void	exec_cmd(t_token *token, t_global *shell)
{
	if (token->make_a_pipe && pipe(token->pipe_fd) == -1)
		exec_cmd_error(shell, ERR_PIPE, token);
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
		close_redirections(token);
		exit(EXIT_FAILURE);
	}
	parent_close_pipes(token);
}
