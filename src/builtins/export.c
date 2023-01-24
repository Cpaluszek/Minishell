/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:42 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/24 15:56:21 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Add variable to environment
// Multiple variables can be exported
	// export a="1" b="2" c="3"
#include "minishell.h"
#include "exec.h"

static void		print_sorted_env(t_global *shell);
static void		add_env_variable(t_global *shell, char *cmd);

int	ft_export(t_token *token, t_global *shell)
{
	int		i;
	int		ret_value;

	ret_value = 0;
	if (args_number(token->cmd) == 1)
	{
		print_sorted_env(shell);
		return (ret_value);
	}
	i = 1;
	while (token->cmd[i])
	{
		if (!is_valid_identifier(token->cmd[i]))
		{
			ft_printf_fd(STDERR, "export: `%s' not a valid identifier\n", \
				token->cmd[i]);
			ret_value = EXIT_FAILURE;
		}
		else
			add_env_variable(shell, token->cmd[i]);
		i++;
	}
	update_env(shell);
	return (ret_value);
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
		error_exit_shell(shell, ERR_MALLOC);
	search_result = search_in_env(shell->env_list, cmd);
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
