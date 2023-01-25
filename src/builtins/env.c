/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:36 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/25 15:24:52 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Print a list of environement variables
#include "minishell.h"
#include "exec.h"

/**
 * @brief Print the environment
 * 
 * @param token (void)
 * @param shell structure containing environment
 * @return 1 if there is options or arguments
 */
int	ft_env(t_token *token, t_global *shell)
{
	int	i;

	token->pid = fork();
	if (token->pid == -1)
		error_exit_shell(shell, ERR_FORK);
	if (token->pid != 0)
		return (EXIT_SUCCESS);
	if (dup_fds(token))
		exit(EXIT_FAILURE);
	if (args_number(token->cmd) > 1)
		return (1);
	i = 0;
	while (shell->env[i])
	{
		printf("%s\n", shell->env[i]);
		i++;
	}
	exit(EXIT_SUCCESS);
}
