/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_reset_parsing.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 09:52:00 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/02/15 20:36:15 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_list_functions.h"
#include "parsing.h"
#include "minishell.h"
#include "env.h"

static t_list	*make_env_list(t_global *shell, char **env);

void	set_environment(t_global *shell, char **env)
{
	shell->input = NULL;
	shell->path = NULL;
	shell->token_list = NULL;
	shell->block_list = NULL;
	shell->input_completed = NULL;
	shell->block_fd_list = NULL;
	shell->nb_open_parenthesis = 0;
	if (env != NULL && env[0] == NULL)
		shell->env = set_minimum_env();
	else
	{
		shell->env = ft_tab_strdup(env);
		increment_shlvl(shell);
	}
	test_failed_malloc(shell, env);
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
		path = ft_strnstr(env[i], "PATH=", 5);
		if (path)
			break ;
		i++;
	}
	if (!path)
		return (NULL);
	cmd_path = ft_split(&path[5], ':');
	test_failed_malloc(shell, cmd_path);
	return (cmd_path);
}

static t_list	*make_env_list(t_global *shell, char **env)
{
	t_list	*env_list;
	t_list	*env_str;
	char	*temp;
	int		i;

	env_list = NULL;
	i = 0;
	while (env[i])
	{
		temp = ft_strdup(env[i++]);
		if (!temp)
		{
			ft_lstclear(&env_list, free);
			error_exit_shell(shell, ERR_MALLOC);
		}
		env_str = ft_lstnew(temp);
		if (!env_str)
		{
			free(temp);
			ft_lstclear(&env_list, free);
			error_exit_shell(shell, ERR_MALLOC);
		}
		ft_lstadd_back(&env_list, env_str);
	}
	return (env_list);
}

void	reset_commands(t_global	*shell)
{
	t_list	*tok;

	ft_free(shell->input);
	ft_free_split(shell->path);
	shell->input = NULL;
	ft_free(shell->input_completed);
	shell->input_completed = NULL;
	shell->command_line = BEGIN;
	shell->nb_open_parenthesis = 0;
	tok = shell->block_fd_list;
	while (tok)
	{
		dprintf(1, "fd %p = %d\n", (int *)tok->content, *(int *)tok->content);
		tok = tok->next;
	}
	close_all_file_descriptors(shell->block_fd_list);
	ft_lstclear(&shell->block_fd_list, NULL);
	// ft_lstclear_token(&shell->token_list);
	ft_lstclear_block(&shell->block_list);
	shell->token_list = NULL;
	shell->block_list = NULL;
}
