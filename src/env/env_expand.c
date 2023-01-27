/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 09:44:58 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/27 11:52:57 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "errors.h"
#include "env.h"

#define VAR_LIMITER "$ \n\"\'"

static char	*replace_var_env(t_global *shell, char *ret, char *pos, int *len);
static void	alloc_error_in_expand(t_global *shell, char *buff, char *ret);

// Todo: check for $? - and $ alone
// Note: in here_doc quotes doesn't matter, but in parsing its different
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
		ret = replace_var_env(shell, ret, pos, &len);
		if (ret == NULL)
			alloc_error_in_expand(shell, buff, ret);
		pos += len + 1;
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
		buff = pos + len;
	}
	if (ret == NULL)
		return (buff);
	return (ret);
}

static char	*replace_var_env(t_global *shell, char *ret, char *pos, int *len)
{
	char	*content;
	char	*temp;
	t_list	*lst;

	*len = 0;
	temp = NULL;
	lst = shell->env_list;
	while (pos[*len + 1] && ft_strchr(VAR_LIMITER, pos[*len + 1]) == NULL)
		(*len)++;
	while (lst)
	{
		content = (char *)(lst->content);
		if (ft_strncmp(content, pos + 1, *len) == 0 && content[*len] == '=')
		{
			temp = content + *len + 1;
			break ;
		}
		lst = lst->next;
	}
	if (temp != NULL)
		ret = ft_strjoin_and_free(ret, temp);
	return (ret);
}

static void	alloc_error_in_expand(t_global *shell, char *buff, char *ret)
{
	ft_free(ret);
	ft_free(buff);
	error_exit_shell(shell, ERR_MALLOC);
}
