/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 08:39:22 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/30 15:50:55 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

static void	expand_dollar(t_global *shell, t_token *token, char *str);
static char	*get_variable(t_global *shell, char **env, char *var);

void	expand_variables(t_global *shell)
{
	t_token	*token;

	token = shell->token_list;
	while (token)
	{
		if ((token->token == DQUOTE || token->token == CMD) && \
			ft_is_inside('$', token->str))
			expand_dollar(shell, token, token->str);
		token = token->next;
	}
}

static void	expand_dollar(t_global *shell, t_token *token, char *str)
{
	char	*var;
	char	*expanded_str;
	int		i;
	int 	start;
	
	var = ft_strchr(str, '$');
	if (!var)
		return ;
	start = var - str;
	if (var[1] == '?')
	{
		var = ft_itoa(g_status);
		test_failed_malloc(shell, var);
		expanded_str = ft_strndup(str, start);
		test_failed_malloc(shell, expanded_str);
		expanded_str = ft_strjoin_and_free(expanded_str, var);
		ft_free(var);
		test_failed_malloc(shell, expanded_str);
		expanded_str = ft_strjoin_and_free(expanded_str, &str[start + 2]);
		test_failed_malloc(shell, expanded_str);
		token->str = expanded_str;
		expand_dollar(shell, token, token->str);
	}
	else
	{
		i = 1;
		while (var[i] && ft_isalnum(var[i]))
			i++;
		var = ft_strndup(&var[1], i - 1);
		test_failed_malloc(shell, var);
		var = ft_strjoin_and_free(var, "=");
		test_failed_malloc(shell, var);
		var = get_variable(shell, shell->env, var);
		expanded_str = ft_strndup(str, start);
		test_failed_malloc(shell, expanded_str);
		expanded_str = ft_strjoin_and_free(expanded_str, var);
		ft_free(var);
		test_failed_malloc(shell, expanded_str);
		expanded_str = ft_strjoin_and_free(expanded_str, &str[start + i]);
		test_failed_malloc(shell, expanded_str);
		token->str = expanded_str;
		expand_dollar(shell, token, token->str);
	}
}

static char	*get_variable(t_global *shell, char **env, char *var)
{
	int		i;
	int		len;
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
	return (NULL);
}