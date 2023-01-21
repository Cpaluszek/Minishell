/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:42 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/21 10:54:37 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Add variable to environment
// Multiple variables can be exported
	// export a="1" b="2" c="3"
#include "structs.h"
#include "exec.h"
#include <stdio.h>
#include <unistd.h>

static void	print_sorted_env(t_global *shell);
static void	*copy_content_str(void *entry);
static int	cmp_str(void *data1, void *data2);

int	ft_export(t_token *token, t_global *shell)
{
	(void) shell;
	if (args_number(token->cmd) == 1)
	{
		print_sorted_env(shell);
		return (0);
	}
	// Todo: add variables to env
	return (0);
}

// Todo: protect lstmap return
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

static int	cmp_str(void *data1, void *data2)
{
	if (data1 && data2)
		return (ft_strcmp((char *)data1, (char *)data2));
	return (0);
}

static void	*copy_content_str(void *entry)
{
	char	*str;

	str = (char *)entry;
	return (ft_strdup(str));
}
