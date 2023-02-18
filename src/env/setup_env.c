/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:13:43 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/18 11:00:47 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "exec.h"
#include "minishell.h"

#define DEFAULT_SHLVL	"SHLVL=1"
#define PWD_PREFIX		"PWD="
#define ENV_UNDERSC		"_=/usr/bin/env"
#define SHLVL_PREFIX	"SHLVL="

static void	err_alloc(char **env);
static void	add_shlvl_to_env(t_global *sh);

char	**set_minimum_env(void)
{
	char	**env;
	char	*pwd;

	env = malloc(sizeof(char *) * 4);
	if (env == NULL)
		err_alloc(NULL);
	pwd = ft_getcwd();
	if (pwd == NULL)
		err_alloc(env);
	env[0] = ft_strjoin(PWD_PREFIX, pwd);
	free(pwd);
	if (env[0] == NULL)
		err_alloc(env);
	env[1] = ft_strdup("SHLVL=0");
	if (env[1] == NULL)
		err_alloc(env);
	env[2] = ft_strdup(ENV_UNDERSC);
	if (env[2] == NULL)
		err_alloc(env);
	env[3] = NULL;
	return (env);
}

void	increment_shlvl(t_global *sh)
{
	int		i;
	char	*pos;
	char	*shlvl_str;

	i = 0;
	while (sh->env[i])
	{
		if (ft_strncmp(sh->env[i], SHLVL_PREFIX, ft_strlen(SHLVL_PREFIX)) == 0)
		{
			pos = ft_strchr(sh->env[i], '=') + 1;
			shlvl_str = ft_itoa(ft_atoi(pos) + 1);
			if (shlvl_str == NULL)
				error_exit_shell(sh, ERR_MALLOC);
			ft_free(sh->env[i]);
			sh->env[i] = ft_strjoin_and_free_s2(SHLVL_PREFIX, shlvl_str);
			if (sh->env[i] == NULL)
				error_exit_shell(sh, ERR_MALLOC);
			break ;
		}
		i++;
	}
	if (sh->env[i] == NULL)
		add_shlvl_to_env(sh);
}

static void	add_shlvl_to_env(t_global *sh)
{
	char	**new_env;
	int		i;

	i = 0;
	while (sh->env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (new_env == NULL)
		error_exit_shell(sh, ERR_MALLOC);
	i = 0;
	while (sh->env[i])
	{
		new_env[i] = sh->env[i];
		i++;
	}
	new_env[i] = ft_strdup(DEFAULT_SHLVL);
	if (new_env[i] == NULL)
		error_exit_shell(sh, ERR_MALLOC);
	new_env[i + 1] = NULL;
	free(sh->env);
	sh->env = new_env;
}

static void	err_alloc(char **env)
{
	if (env != NULL)
		ft_free(env);
	ft_putendl_fd(ERR_MALLOC, STDERR);
	exit(EXIT_FAILURE);
}
