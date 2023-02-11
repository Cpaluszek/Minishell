/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 09:44:58 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/11 10:53:21 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "errors.h"
#include "env.h"

static char	*replace_var_env(t_list *env_lst, char *ret, char **pos, int len);
static char	*copy_until_next(t_global *sh, char *buff, char *ret, char **pos);
static char	*init_ret_str(t_global *shell, char *buff, char *pos);
static void	alloc_error_in_expand(t_global *shell, char *buff, char *ret);

// Note: quotes doesn't matter in here_doc, but not in parsing
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
		ret = replace_var_env(shell->env_list, ret, &pos, 0);
		if (ret == NULL)
			alloc_error_in_expand(shell, buff, ret);
		ret = copy_until_next(shell, buff, ret, &pos);
	}
	if (ret == NULL)
		return (buff);
	return (ret);
}

static char	*replace_var_env(t_list *env_lst, char *ret, char **pos, int len)
{
	char	*temp;
	char	*content;

	temp = NULL;
	while ((*pos)[len + 1] && ft_strchr(VAR_LIMITER, (*pos)[len + 1]) == NULL)
		len++;
	if (len == 0)
		temp = ft_strdup("$");
	else if ((*pos)[1] == '?')
		temp = ft_itoa(g_status);
	if (temp == NULL && (len == 0 || (*pos)[1] == '?'))
		return (ft_free(ret), NULL);
	while (env_lst && len > 0 && temp == NULL)
	{
		content = (char *)env_lst->content;
		if (ft_strncmp(content, (*pos) + 1, len) == 0 && content[len] == '=')
			temp = content + len + 1;
		env_lst = env_lst->next;
	}
	*pos += len + 1;
	return (ft_strjoin_and_free(ret, temp));
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

static char	*init_ret_str(t_global *shell, char *buff, char *pos)
{
	char	*ret;

	ret = ft_strndup(buff, pos - buff);
	if (ret == NULL)
		alloc_error_in_expand(shell, buff, NULL);
	return (ret);
}

static void	alloc_error_in_expand(t_global *shell, char *buff, char *ret)
{
	ft_free(ret);
	ft_free(buff);
	error_exit_shell(shell, ERR_MALLOC);
}
