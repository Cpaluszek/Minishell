/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:49:08 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/10 11:07:45 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "structs.h"

int	cmp_str(void *data1, void *data2)
{
	if (data1 && data2)
		return (ft_strcmp((char *)data1, (char *)data2));
	return (0);
}

void	*copy_content_str(void *entry)
{
	char	*str;

	str = (char *)entry;
	if (str == NULL)
		return (NULL);
	return (ft_strdup(str));
}

int	any_pipe_in_token_list(t_token *token)
{
	t_token	*origin;

	origin = token;
	while (token)
	{
		if (token->token == PIPE)
			return (1);
		token = token->next;
	}
	token = origin;
	while (token)
	{
		if (token->token == PIPE)
			return (1);
		token = token->prev;
	}
	return (0);
}

int	args_number(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}
