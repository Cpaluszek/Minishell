/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimum_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:13:43 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/30 15:34:55 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "errors.h"
#include "exec.h"

#define DEFAULT_SHLVL	"SHLVL=1"
#define PWD_PREFIX		"PWD="

static void	err_alloc(char **env);

// PWD
// SHLVL
// NULL
char	**set_minimum_env(void)
{
	char	**env;
	char	*pwd;

	env = malloc(sizeof(char *) * 3);
	if (env == NULL)
		err_alloc(NULL);
	pwd = ft_getcwd();
	if (pwd == NULL)
		err_alloc(env);
	env[0] = ft_strjoin(PWD_PREFIX, pwd);
	free(pwd);
	if (env[0] == NULL)
		err_alloc(env);
	env[1] = ft_strdup(DEFAULT_SHLVL);
	if (env[1] == NULL)
		err_alloc(env);
	env[2] = NULL;
	return (env);
}

static void	err_alloc(char **env)
{
	if (env != NULL)
		ft_free(env);
	ft_putendl_fd(ERR_MALLOC, STDERR);
	exit(EXIT_FAILURE);
}
