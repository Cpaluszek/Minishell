/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:29 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/18 17:03:33 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// change current working directory
// only with relative or absolute path
#include "structs.h"
#include "exec.h"
#include <unistd.h>
#include <stdio.h>

static void	update_oldpwd(t_global *shell);
static char	*cd_home(t_global *shell);
static char	*cd_old(t_global *shell);

// Todo: test with directory without permissions
// Todo: add cd ~, real cd is not searching in env
int	ft_cd(t_token *token, t_global *shell)
{
	char	*target;

	if (args_number(token->cmd) > 2)
	{
		ft_printf_fd(STDERR_FILENO, "cd: too many arguments\n");
		target = NULL;
	}
	else if (args_number(token->cmd) == 1)
		target = cd_home(shell);
	else if (ft_strcmp(token->cmd[1], "-") == 0)
		target = cd_old(shell);
	else
		target = token->cmd[1];
	if (target == NULL)
		return (1);
	if (chdir(target) == -1)
	{
		ft_printf_fd(STDERR_FILENO, \
			"cd: %s: No such file or directory\n", target);
		return (1);
	}
	update_oldpwd(shell);
	return (0);
}

static void	update_oldpwd(t_global *shell)
{
	(void) shell;
	printf("update OLDPWD\n");
	// Todo: regenerate env
}

// Note: refacto in one function ?
static char	*cd_home(t_global *shell)
{
	t_list	*home_var;

	home_var = search_in_env(shell->env_list, "HOME=");
	if (home_var == NULL)
	{
		ft_printf_fd(STDERR_FILENO, "cd: HOME not set\n");
		return (NULL);
	}
	return (home_var->content);
}

static char *cd_old(t_global *shell)
{
	t_list	*old_var;

	old_var = search_in_env(shell->env_list, "OLDPWD=");
	if (old_var == NULL)
	{
		ft_printf_fd(STDERR_FILENO, "cd: OLDPWD not set\n");
		return (NULL);
	}
	return (old_var->content);
}
