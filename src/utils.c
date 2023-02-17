/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:37:58 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/15 22:51:44 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token_list_functions.h"
#include "errors.h"
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>

// void	close_all_file_descriptors(t_list *fd_list);

void	free_structs(t_global *shell)
{
	ft_free_split(shell->env);
	ft_free_split(shell->path);
	ft_lstclear_token(&shell->token_list);
	ft_lstclear(&shell->env_list, free);
	ft_lstclear(&shell->block_fd_list, NULL);
	// ft_lstclear(&shell->garbage_block_list, NULL);
	// close_all_file_descriptors(shell->block_fd_list);
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

void	exit_shell_from_signal(t_global *shell)
{
	if (isatty(STDIN) && tcsetattr(0, TCSANOW, &shell->saved_attr) == -1)
		perror(ERR_TCSET);
	printf("exit\n");
	rl_clear_history();
	free_structs(shell);
	exit(g_status);
}

