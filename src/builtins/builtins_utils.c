/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:49:08 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/25 11:50:22 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

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