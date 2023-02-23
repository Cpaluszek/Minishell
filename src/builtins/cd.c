/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:29 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/18 11:57:15 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "env.h"
#include <dirent.h>

#define HOME_VAR	"HOME="
#define OLDPWD_VAR	"OLDPWD="
#define PWD_VAR		"PWD="

static int	change_directory(t_global *shell, char *target);
static void	update_var(t_global *shell, char *new, char *var);
static void	add_oldpwd_to_env(t_global *shell, char *new);
static char	*cd_env_var(t_global *shell, char *var_name);

int	ft_cd(t_token *token, t_global *shell)
{
	char	*target;
	DIR		*dir_access;

	target = NULL;
	if (args_number(token->cmd) > 2)
		ft_printf_fd(STDERR, "cd: too many arguments\n");
	else if (args_number(token->cmd) == 1 || ft_strcmp(token->cmd[1], "~") == 0)
		target = cd_env_var(shell, HOME_VAR);
	else if (ft_strcmp(token->cmd[1], "-") == 0)
		target = cd_env_var(shell, OLDPWD_VAR);
	else
		target = token->cmd[1];
	if (target == NULL)
		return (EXIT_FAILURE);
	if (any_pipe_in_token_list(token))
	{
		dir_access = opendir(target);
		if (dir_access == NULL)
		{
			ft_printf_fd(STDERR, "cd: %s: ", target);
			return (perror(""), EXIT_FAILURE);
		}
		return (closedir(dir_access), EXIT_SUCCESS);
	}
	return (change_directory(shell, target));
}

static int	change_directory(t_global *shell, char *target)
{
	char	*pwd;

	pwd = ft_getcwd();
	if (chdir(target) == -1)
	{
		ft_printf_fd(STDERR, "cd: %s: ", target);
		perror("");
		free(pwd);
		return (1);
	}
	if (pwd != NULL)
		update_var(shell, pwd, OLDPWD_VAR);
	pwd = ft_getcwd();
	if (pwd != NULL)
		update_var(shell, pwd, PWD_VAR);
	return (0);
}

static void	update_var(t_global *shell, char *new, char *var)
{
	char	*temp;
	t_list	*env_var;

	env_var = search_in_env(shell->env_list, var);
	if (env_var == NULL)
	{
		if (ft_strcmp(var, OLDPWD_VAR) == 0)
			add_oldpwd_to_env(shell, new);
		return ;
	}
	free(env_var->content);
	temp = ft_strjoin_and_free_s2(var, new);
	if (temp == NULL)
		error_exit_shell(shell, ERR_MALLOC);
	env_var->content = temp;
	update_env(shell);
}

static void	add_oldpwd_to_env(t_global *shell, char *new)
{
	char	*old_pwd;

	old_pwd = ft_strjoin_and_free_s2(OLDPWD_VAR, new);
	if (old_pwd == NULL)
		error_exit_shell(shell, ERR_MALLOC);
	add_env_variable(shell, old_pwd);
	free(old_pwd);
}

static char	*cd_env_var(t_global *shell, char *var_name)
{
	t_list	*var;
	char	*target;
	int		i;

	i = 0;
	var = search_in_env(shell->env_list, var_name);
	if (var == NULL)
	{
		ft_putstr_fd("cd: ", STDERR);
		while (var_name[i] && var_name[i] != '=')
			i++;
		write(STDERR, var_name, i);
		ft_putstr_fd(" not set\n", STDERR);
		return (NULL);
	}
	target = var->content + ft_strlen(var_name);
	return (target);
}
