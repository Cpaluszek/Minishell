/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:49:08 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/25 17:06:06 by cpalusze         ###   ########.fr       */
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

int	check_pipes_in_token_list(t_token *token)
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
