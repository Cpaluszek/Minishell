/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 08:39:22 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/27 11:02:35 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	expand_variables(t_global *shell)
{
	t_token	*token;

	token = shell->token_list;
	while (token)
	{
		if ((token->token == QUOTE || token->token == CMD)) \
			&& ft_is_inside(token->str, '$')
			expand_dollar(shell, token–>str);
		token = token->next;
	}
}

void	expand_dollar(t_global *shell, char *str)
{
	char	*var;
	char	*new_var;
	char	*expanded_str;
	int		i;
	int 	start;
	
	var = ft_strchr(str, '$');
	if (!var)
		return ;
	start = var - str;
	i = 0;
	while (var[i] && var[i] != ' ')
		i++;
	var = ft_substr(var, 1, i);
	test_failed_malloc(shell, var);
	if (temporary_list_expanded_variable(shell, var))
		return ; // check si la variable a expand ne va pas creer une boucle infinir.
	var = ft_strjoin_and_free(var, "=");
	test_failed_malloc(shell, var);
	new_var = get_variable(shell->env, var);
	if (!new_var)
		new_var = var;
	expanded_str = ft_strndup(str, start);
	test_failed_malloc(expanded_str);
	expanded_str = ft_strjoin_and_free(expanded_str, var);
	test_failed_malloc(expanded_str);
	expanded_str = ft_strjoin_and_free(expanded_str, &str[start + i]);
	
}

char	*get_variable(char **env, char *var)
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
			test_failed_malloc(new_var);
			free(var);
			return (new_var);
		}
		i++;
	}
	return (NULL)
}