/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:37:58 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/23 21:28:39 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token_list_functions.h"
#include <stdio.h>
#include <readline/readline.h>

void	free_structs(t_global *shell)
{
	ft_free_split(shell->env);
	ft_free_split(shell->path);
	ft_lstclear_token(&shell->token_list);
	ft_lstclear(&shell->env_list, free);
	ft_free(shell->input);
	ft_free(shell->input_completed);
}

void	error_exit_shell(t_global *shell, char *err_msg)
{
	ft_putstr_fd(err_msg, 2);
	exit_shell(shell, EXIT_FAILURE);
}

void	exit_shell(t_global *shell, int exit_code)
{
	free_structs(shell);
	exit(exit_code);
}

// Todo: print "exit" on the prompt line and not below
void	exit_shell_from_signal(t_global *shell)
{
	tcsetattr(0, TCSANOW, &shell->saved_attr);
	// rl_clear_history();
	printf("exit\n");
	free_structs(shell);
	exit(g_status);
}
