/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:04:17 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/23 13:22:00 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

static void	expand_variable(t_global *shell, t_token *token, \
	char *str, int start);
static void	expand_exit_status(t_global *shell, t_token *token, \
	char *str, int start);
static void	no_expand(t_global *shell, t_token *token, char *str, int len);
static char	*get_variable(t_global *shell, char **env, char *var);
void		test_failed_malloc(t_global *shell, void *content);

void	expand_dollar(t_global *shell, t_token *token, char *str)
{
	char	*var;
	int		start;

	var = ft_strchr(str, '$');
	if (!var)
		return ;
	start = var - str;
	if (var[1] == '?')
		expand_exit_status(shell, token, str, start);
	else if (!ft_isalnum(var[1]))
		no_expand(shell, token, str, start + 1);
	else
		expand_variable(shell, token, str, start);
}

static void	expand_variable(t_global *shell, t_token *token, \
	char *str, int start)
{
	char	*expanded_str;
	char	*variable;
	int		i;

	i = 1;
	while (str[start + i] && ft_isalnum(str[start + i]))
		i++;
	variable = ft_strndup(&str[start + 1], i - 1);
	test_failed_malloc(shell, variable);
	variable = ft_strjoin_and_free(variable, "=");
	test_failed_malloc(shell, variable);
	variable = get_variable(shell, shell->env, variable);
	expanded_str = ft_strndup(str, start);
	test_failed_malloc(shell, expanded_str);
	expanded_str = ft_strjoin_and_free(expanded_str, variable);
	ft_free(variable);
	test_failed_malloc(shell, expanded_str);
	expanded_str = ft_strjoin_and_free(expanded_str, &str[start + i]);
	test_failed_malloc(shell, expanded_str);
	free(token->str);
	token->str = expanded_str;
	expand_dollar(shell, token, token->str);
}

static void	expand_exit_status(t_global *shell, t_token *token, \
	char *str, int start)
{
	char	*expanded_str;
	char	*exit_code;

	exit_code = ft_itoa(g_status);
	test_failed_malloc(shell, exit_code);
	expanded_str = ft_strndup(str, start);
	test_failed_malloc(shell, expanded_str);
	expanded_str = ft_strjoin_and_free(expanded_str, exit_code);
	free(exit_code);
	test_failed_malloc(shell, expanded_str);
	expanded_str = ft_strjoin_and_free(expanded_str, &str[start + 2]);
	test_failed_malloc(shell, expanded_str);
	free(token->str);
	token->str = expanded_str;
	expand_dollar(shell, token, token->str);
}

static void	no_expand(t_global *shell, t_token *token, char *str, int len)
{
	char	*already_expanded;
	char	*missing_expanded;

	already_expanded = ft_substr(str, 0, len);
	test_failed_malloc(shell, already_expanded);
	token->temp_expand = ft_strjoin_and_free(token->temp_expand, \
		already_expanded);
	free(already_expanded);
	test_failed_malloc(shell, token->temp_expand);
	missing_expanded = ft_substr(str, len, ft_strlen(str));
	test_failed_malloc(shell, missing_expanded);
	free(token->str);
	token->str = missing_expanded;
	expand_dollar(shell, token, token->str);
}

static char	*get_variable(t_global *shell, char **env, char *var)
{
	int		i;
	size_t	len;
	char	*new_var;

	len = ft_strlen(var);
	i = 0;
	while (env[i])
	{
		new_var = ft_strnstr(env[i], var, len);
		if (new_var)
		{
			new_var = ft_substr(new_var, len, ft_strlen(new_var));
			test_failed_malloc(shell, new_var);
			free(var);
			return (new_var);
		}
		i++;
	}
	free(var);
	return (NULL);
}
