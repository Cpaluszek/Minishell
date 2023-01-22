/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_reset_parsing.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 09:52:00 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/01/22 16:24:14 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_list_functions.h"
#include "parsing.h"
#include "structs.h"
#include "libft.h"

static t_list	*make_env_list(t_global *shell, char **env);

// Todo: set minimal env when `env -i`
	// PWD - SHLVL=1 - _=/usr/bin/env
void	set_environment(t_global *shell, char **env)
{
	shell->input = NULL;
	shell->token_list = NULL;
	shell->block_list = NULL;
	shell->input_completed = NULL;
	shell->env = ft_tab_strdup(env);
	if (!shell->env)
		error_exit_parsing(shell, ERR_MALLOC);
	shell->env_list = make_env_list(shell, env);
}

/**
 * Function that retrieve the "PATH" environment of the program.
 * @param shell
 * @param env
*/
char	**get_path(t_global *shell, char **env)
{
	char	*path;
	char	**cmd_path;
	int		i;

	i = 0;
	while (env[i])
	{
		path = ft_strnstr(env[i], "PATH=", 10);
		if (path)
			break ;
		i++;
	}
	if (!path)
		return (NULL);
	cmd_path = ft_split(&path[5], ':');
	if (!(cmd_path))
		error_exit_parsing(shell, ERR_MALLOC);
	return (cmd_path);
}

// Note: dup env[i] - to free boths ?
static t_list	*make_env_list(t_global *shell, char **env)
{
	t_list	*env_list;
	t_list	*env_str;
	int		i;

	env_list = NULL;
	i = 0;
	while (env[i])
	{
		env_str = ft_lstnew(env[i]);
		if (!env_str)
		{
			ft_lstclear(&env_list, free);
			error_exit_parsing(shell, ERR_MALLOC);
		}
		ft_lstadd_back(&env_list, env_str);
		i++;
	}
	return (env_list);
}

void	reset_commands(t_global	*shell)
{
	ft_free(shell->input);
	shell->input = NULL;
	ft_free(shell->input_completed);
	shell->input_completed = NULL;
	shell->command_line = BEGIN;
	ft_lstclear_block(&shell->block_list);
	shell->token_list = NULL;
	shell->block_list = NULL;
}
