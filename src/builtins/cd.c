/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:29 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/23 11:32:24 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// change current working directory
// only with relative or absolute path
#include "structs.h"
#include "exec.h"

#define HOME_VAR	"HOME="
#define OLDPWD_VAR	"OLDPWD="

static void	update_oldpwd(t_global *shell, char *old_pwd);
static char	*cd_home(t_global *shell);
static char	*cd_old(t_global *shell);

// Todo: test with directory without permissions
// Todo: add cd ~, real cd is not searching in env
int	ft_cd(t_token *token, t_global *shell)
{
	char	*target;
	char	*old_pwd;

	if (args_number(token->cmd) > 2)
	{
		ft_printf_fd(STDERR, "cd: too many arguments\n");
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
	old_pwd = ft_getcwd();
	if (chdir(target) == -1)
	{
		ft_printf_fd(STDERR, "cd: %s: No such file or directory\n", target);
		free(old_pwd);
		return (1);
	}
	update_oldpwd(shell, old_pwd);
	return (0);
}

static void	update_oldpwd(t_global *shell, char *old_pwd)
{
	char	*temp;
	t_list	*oldpwd_var;

	oldpwd_var = search_in_env(shell->env_list, OLDPWD_VAR);
	if (oldpwd_var == NULL)
		return ;
	free(oldpwd_var->content);
	temp = ft_strjoin(OLDPWD_VAR, old_pwd);
	if (temp == NULL)
		error_exit_exec(shell, ERR_MALLOC);
	free(old_pwd);
	oldpwd_var->content = temp;
	update_env(shell);
}

// Note: refacto in one function ?
static char	*cd_home(t_global *shell)
{
	t_list	*home_var;

	home_var = search_in_env(shell->env_list, HOME_VAR);
	if (home_var == NULL)
	{
		ft_printf_fd(STDERR, "cd: HOME not set\n");
		return (NULL);
	}
	return (home_var->content);
}

static char	*cd_old(t_global *shell)
{
	t_list	*old_var;

	old_var = search_in_env(shell->env_list, OLDPWD_VAR);
	if (old_var == NULL)
	{
		ft_printf_fd(STDERR, "cd: OLDPWD not set\n");
		return (NULL);
	}
	return (old_var->content);
}
