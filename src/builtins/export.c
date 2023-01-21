/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:42 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/21 15:33:21 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Add variable to environment
// Multiple variables can be exported
	// export a="1" b="2" c="3"
#include "structs.h"
#include "exec.h"
#include <stdio.h>
#include <unistd.h>

static void		print_sorted_env(t_global *shell);
static void		add_env_variable(t_global *shell, char *cmd);

// Todo: exit code - test with bash3.2
int	ft_export(t_token *token, t_global *shell)
{
	int		i;

	if (args_number(token->cmd) == 1)
	{
		print_sorted_env(shell);
		return (0);
	}
	i = 1;
	while (token->cmd[i])
	{
		if (!is_valid_identifier(token->cmd[i]))
		{
			ft_printf_fd(STDERR_FILENO, "export: `%s' not a valid identifier\n", \
				token->cmd[i]);
			g_status = 1;
		}
		else
		{
			add_env_variable(shell, token->cmd[i]);
			g_status = 0;
		}
		i++;
	}
	update_env(shell);
	return (0);
}

// Todo: protect lstmap return
// Todo: add `declare -x` prefix
static void	print_sorted_env(t_global *shell)
{
	t_list	*sorted_env;
	t_list	*current;

	sorted_env = ft_lstmap(shell->env_list, &copy_content_str, &free);
	ft_lstsort(&sorted_env, &cmp_str);
	current = sorted_env;
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	ft_lstclear(&sorted_env, &free);
}

static void	add_env_variable(t_global *shell, char *cmd)
{
	char	*new_content;
	t_list	*search_result;
	t_list	*new;

	new_content = ft_strdup(cmd);
	if (new_content == NULL)
		error_exit_exec(shell, "Alloc error\n");
	search_result = search_identifier(shell->env_list, cmd);
	if (search_result == NULL)
	{
		new = ft_lstnew(new_content);
		ft_lstadd_back(&(shell->env_list), new);
	}
	else
	{
		free(search_result->content);
		search_result->content = new_content;
	}
}
