/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:45 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/25 15:25:01 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

/**
 * @brief writes the absolute pathname of the current working directory to STDOUT
 * 
 * @param token (void)
 * @param shell (void)
 * @return 1 on error, 0 otherwise
 */
int	ft_pwd(t_token *token, t_global *shell)
{
	char	*pwd;

	token->pid = fork();
	if (token->pid == -1)
		error_exit_shell(shell, ERR_FORK);
	if (token->pid != 0)
		return (EXIT_SUCCESS);
	if (dup_fds(token))
		exit(EXIT_FAILURE);
	pwd = ft_getcwd();
	if (pwd == NULL)
		return (1);
	printf("%s\n", pwd);
	free(pwd);
	exit(EXIT_SUCCESS);
}

char	*ft_getcwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		perror("getcwd() error");
	return (pwd);
}
