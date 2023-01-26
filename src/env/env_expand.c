/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 09:44:58 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/26 15:17:14 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "errors.h"
#include "env.h"

#define VAR_LIMITER "$ \n\"\'"

static char	*search_var_env(t_list *env_list, char *name, int len);
static void	alloc_error_in_expand(t_global *shell, char *buff, char *ret);

// Todo: check for $?
char	*check_for_expand(t_global *shell, char *buff)
{
	char	*pos;
	char	*ret;
	char	*temp;
	int		len;

	pos = buff;
	ret = NULL;
	while (1)
	{
		pos = ft_strchr(buff, '$');
		if (pos == NULL)
			break ;
		if (ret == NULL)
		{
			ret = ft_strndup(buff, pos - buff);
			if (ret == NULL)
				alloc_error_in_expand(shell, buff, NULL);
		}
		buff = pos;
		len = 0;
		while (pos[len + 1] && ft_strchr(VAR_LIMITER, pos[len + 1]) == NULL)
			len++;
		temp = search_var_env(shell->env_list, pos + 1, len);
		if (temp != NULL)
		{
			ret = ft_strjoin_and_free(ret, temp);
			if (ret == NULL)
				alloc_error_in_expand(shell, buff, ret);
		}
		pos += len + 1;
		buff += len + 1;
		len = 0;
		while (pos[len] && pos[len] != '$')
			len++;
		temp = ft_strndup(pos, len);
		if (temp == NULL)
			alloc_error_in_expand(shell, buff, ret);
		ret = ft_strjoin_and_free(ret, temp);
		ft_free(temp);
		if (ret == NULL)
			alloc_error_in_expand(shell, buff, ret);
		buff += len;
	}
	return (ret);
}

static void	alloc_error_in_expand(t_global *shell, char *buff, char *ret)
{
	ft_free(ret);
	ft_free(buff);
	error_exit_shell(shell, ERR_MALLOC);
}

static char	*search_var_env(t_list *env_list, char *name, int len)
{
	char	*content;

	while (env_list)
	{
		content = (char *)(env_list->content);
		if (ft_strncmp(content, name, len) == 0 && content[len] == '=')
			return (content + len + 1);
		env_list = env_list->next;
	}
	return (NULL);
}
