/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:42 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/26 09:50:21 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include "exec.h"
#define EXPORT_PREFIX	"declare -x "

static void		print_sorted_env(t_token *token, t_global *shell);
static void		print_env_variable(char *str);

// Todo: unclosed quotes should not work
int	ft_export(t_token *token, t_global *shell)
{
	int		i;
	int		ret_value;

	ret_value = 0;
	if (args_number(token->cmd) == 1)
	{
		print_sorted_env(token, shell);
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

static void	print_sorted_env(t_token *token, t_global *shell)
{
	t_list	*sorted_env;
	t_list	*current;

	token->pid = fork();
	if (token->pid == -1)
		error_exit_shell(shell, ERR_FORK);
	if (token->pid != 0)
		return ;
	if (dup_fds(token))
		exit(EXIT_FAILURE);
	sorted_env = ft_lstmap(shell->env_list, &copy_content_str, &free);
	if (sorted_env == NULL)
		error_exit_shell(shell, ERR_MALLOC);
	ft_lstsort(&sorted_env, &cmp_str);
	current = sorted_env;
	while (current)
	{
		print_env_variable((char *)current->content);
		current = current->next;
	}
	ft_lstclear(&sorted_env, &free);
	exit(EXIT_SUCCESS);
}

static void	print_env_variable(char *str)
{
	int	i;

	i = 0;
	ft_putstr_fd(EXPORT_PREFIX, STDOUT);
	while (str[i] && str[i] != '=')
		write(STDOUT, &str[i++], 1);
	if (!str[i])
	{
		write(STDOUT, "\n", 1);
		return ;
	}
	write(STDOUT, &str[i++], 1);
	write(STDOUT, "\"", 1);
	while (str[i])
		write(STDOUT, &str[i++], 1);
	write(STDOUT, "\"\n", 2);
}
