/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:29 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/25 11:12:59 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// change current working directory
// only with relative or absolute path
#include "minishell.h"
#include "exec.h"

#define HOME_VAR	"HOME="
#define OLDPWD_VAR	"OLDPWD="

static int	change_directory(t_global *shell, char *target);
static void	update_oldpwd(t_global *shell, char *old_pwd);
static char	*cd_env_var(t_global *shell, char *var_name);
// static char	*cd_home(t_global *shell);
// static char	*cd_old(t_global *shell);

int	ft_cd(t_token *token, t_global *shell)
{
	char	*target;

	if (args_number(token->cmd) > 2)
	{
		ft_printf_fd(STDERR, "cd: too many arguments\n");
		target = NULL;
	}
	else if (args_number(token->cmd) == 1 || ft_strcmp(token->cmd[1], "~") == 0)
		target = cd_env_var(shell, HOME_VAR);
	else if (ft_strcmp(token->cmd[1], "-") == 0)
		target = cd_env_var(shell, OLDPWD_VAR);
	else
		target = token->cmd[1];
	if (target == NULL)
		return (1);
	return (change_directory(shell, target));
}

static int	change_directory(t_global *shell, char *target)
{
	char	*old_pwd;

	old_pwd = ft_getcwd();
	printf("oldpwd: %s\n", old_pwd);
	printf("change dir to: %s\n", target);
	if (chdir(target) == -1)
	{
		ft_printf_fd(STDERR, "cd: %s: ", target);
		perror("");
		free(old_pwd);
		return (1);
	}
	update_oldpwd(shell, old_pwd);
	// Todo: update PWD
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
		error_exit_shell(shell, ERR_MALLOC);
	free(old_pwd);
	oldpwd_var->content = temp;
	update_env(shell);
}

// Note: refacto in one function ?
static char	*cd_env_var(t_global *shell, char *var_name)
{
	t_list	*var;
	char	*target;
	int		i;

	i = 0;
	var = search_in_env(shell->env_list, HOME_VAR);
	if (var == NULL)
	{
		ft_putstr_fd("cd: ", STDERR);
		while (var_name[i] && var_name[i] != '=')
			i++;
		write(STDERR, var_name, i);
		ft_putstr_fd(" not set\n", STDERR);
		return (NULL);
	}
	target = var->content + ft_strlen(HOME_VAR);
	return (target);
}

// static char	*cd_home(t_global *shell)
// {
// 	t_list	*home_var;
// 	char	*target;

// 	home_var = search_in_env(shell->env_list, HOME_VAR);
// 	if (home_var == NULL)
// 	{
// 		ft_printf_fd(STDERR, "cd: HOME not set\n");
// 		return (NULL);
// 	}
// 	target = home_var->content + ft_strlen(HOME_VAR);
// 	return (target);
// }

// static char	*cd_old(t_global *shell)
// {
// 	t_list	*old_var;
// 	char	*target;

// 	old_var = search_in_env(shell->env_list, OLDPWD_VAR);
// 	if (old_var == NULL)
// 	{
// 		ft_printf_fd(STDERR, "cd: OLDPWD not set\n");
// 		return (NULL);
// 	}
// 	target = old_var->content + ft_strlen(OLDPWD_VAR);
// 	return (target);
// }
