/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 09:44:58 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/27 13:16:40 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "errors.h"
#include "env.h"

#define VAR_LIMITER "$ \n\"\'"

static char	*replace_var_env(t_global *shell, char *ret, char **pos);
static char	*copy_until_next(t_global *sh, char *buff, char *ret, char **pos);
static char	*init_ret_str(t_global *shell, char *buff, char *pos);
static void	alloc_error_in_expand(t_global *shell, char *buff, char *ret);

// Todo: check for $? - and $ alone
// Note: in here_doc quotes doesn't matter, but in parsing its different
char	*check_for_expand(t_global *shell, char *buff)
{
	char	*pos;
	char	*ret;

	pos = buff;
	ret = NULL;
	while (1)
	{
		pos = ft_strchr(pos, '$');
		if (pos == NULL)
			break ;
		if (ret == NULL)
			ret = init_ret_str(shell, buff, pos);
		ret = replace_var_env(shell, ret, &pos);
		if (ret == NULL)
			alloc_error_in_expand(shell, buff, ret);
		ret = copy_until_next(shell, buff, ret, &pos);
	}
	if (ret == NULL)
		return (buff);
	return (ret);
}

static char	*init_ret_str(t_global *shell, char *buff, char *pos)
{
	char	*ret;

	ret = ft_strndup(buff, pos - buff);
	if (ret == NULL)
		alloc_error_in_expand(shell, buff, NULL);
	return (ret);
}

static char	*copy_until_next(t_global *sh, char *buff, char *ret, char **pos)
{
	int		len;
	char	*temp;

	len = 0;
	while ((*pos)[len] && (*pos)[len] != '$')
		len++;
	temp = ft_strndup(*pos, len);
	if (temp == NULL)
		alloc_error_in_expand(sh, buff, ret);
	ret = ft_strjoin_and_free(ret, temp);
	ft_free(temp);
	if (ret == NULL)
		alloc_error_in_expand(sh, buff, ret);
	*pos += len;
	return (ret);
}

static char	*replace_var_env(t_global *shell, char *ret, char **pos)
{
	char	*content;
	char	*temp;
	t_list	*lst;
	int		len;

	len = 0;
	temp = NULL;
	lst = shell->env_list;
	while ((*pos)[len + 1] && ft_strchr(VAR_LIMITER, (*pos)[len + 1]) == NULL)
		len++;
	while (lst)
	{
		content = (char *)(lst->content);
		if (ft_strncmp(content, (*pos) + 1, len) == 0 && content[len] == '=')
		{
			temp = content + len + 1;
			break ;
		}
		lst = lst->next;
	}
	if (temp != NULL)
		ret = ft_strjoin_and_free(ret, temp);
	*pos += len + 1;
	return (ret);
}

static void	alloc_error_in_expand(t_global *shell, char *buff, char *ret)
{
	ft_free(ret);
	ft_free(buff);
	error_exit_shell(shell, ERR_MALLOC);
}
