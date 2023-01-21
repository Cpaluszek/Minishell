/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 12:01:24 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/21 12:37:49 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	return (ft_strdup(str));
}

int	is_allowed_char(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '_');
}
