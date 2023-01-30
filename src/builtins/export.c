/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:42 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/30 15:12:52 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include "exec.h"
#define EXPORT_PREFIX	"declare -x "
#define CONCAT_VAR		"+="

static void		print_sorted_env(t_token *token, t_global *shell);
static void		print_env_variable(char *str);
static void		concat_or_add_var(t_global *shell, char *new, int i);
static int		check_pipes_in_token_list(t_token *token);

// Todo: unclosed quotes should not work
// Todo: if env == NULL
// Todo: export "a     "=test
// Todo: export with pipes should not update env
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
		else if (!check_pipes_in_token_list(token))
			concat_or_add_var(shell, token->cmd[i], 0);
		i++;
	}
	update_env(shell);
	return (ret_value);
}

static void	concat_or_add_var(t_global *shell, char *new, int i)
{
	t_list	*search_result;
	char	*content;
	char	*concat_pos;
	int		j;

	content = ft_calloc(ft_strlen(new) + 1, sizeof(char));
	if (content == NULL)
		error_exit_shell(shell, ERR_MALLOC);
	j = 0;
	while (new[i])
	{
		if (!(new[i] == '+' && i == j))
			content[j++] = new[i];
		i++;
	}
	search_result = search_in_env(shell->env_list, content);
	concat_pos = ft_strnstr(new, CONCAT_VAR, ft_strlen(new));
	if (search_result == NULL || concat_pos == NULL || \
		ft_strchr(new, '=') < concat_pos)
	{
		add_env_variable(shell, content);
		return (free(content));
	}
	free(content);
	concat_env_variable(shell, new, search_result);
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

static int	check_pipes_in_token_list(t_token *token)
{
	t_token	*origin;

	origin = token;
	while (token)
	{
		if (token->make_a_pipe)
			return (1);
		token = token->next;
	}
	token = origin;
	while (token)
	{
		if (token->make_a_pipe)
			return (1);
		token = token->prev;
	}
	return (0);
}
