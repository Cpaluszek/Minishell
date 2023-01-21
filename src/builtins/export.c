/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:42 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/21 15:28:50 by cpalusze         ###   ########.fr       */
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
static int		is_valid_identifier(char *str);
static t_list	*search_identifier(t_list *env_list, char *identifier);
static void		add_variable_to_env(t_global *shell, char *cmd);

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
		printf("env_list size=%d\n", ft_lstsize(shell->env_list));
		if (!is_valid_identifier(token->cmd[i]))
			ft_printf_fd(STDERR_FILENO, "export: `%s' not a valid identifier\n", \
				token->cmd[i]);
		else
			add_variable_to_env(shell, token->cmd[i]);
		i++;
	}

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

/*	Invalid identifiers
*	Can only contains letters (Upper/Lower), underscores, numbers
*	Can't begin with a number
*	Can't be the same as reserved words:
*		! - { - } - case - do - done - elif - else - esac
*		fi - for - function - if - in - select - then
*		until - while
*	Error: `export: <variable-name>: not a valid identifier`
*/
// Todo: check reserved words
static int	is_valid_identifier(char *str)
{
	int	i;

	if (ft_isdigit(str[0]))
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (!is_allowed_char(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static t_list *search_identifier(t_list *env_list, char *identifier)
{
	char	*content;
	int		len;

	while (env_list)
	{
		content = (char *)(env_list->content);
		len = 0;
		while (content[len] && content[len] != '=')
			len++;
		if (ft_strncmp(content, identifier, len) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

static void	add_variable_to_env(t_global *shell, char *cmd)
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
		printf("Add %s to env\n", new_content);
		new = ft_lstnew(new_content);
		ft_lstadd_back(&(shell->env_list), new);
	}
	else
	{
		printf("upate %s to %s\n", (char *)search_result->content, new_content);
		free(search_result->content);
		search_result->content = new_content;
	}
}
