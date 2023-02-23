/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_inside.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:02:37 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/23 13:02:37 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_inside(char c, const char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i++] == c)
			return (1);
	}
	return (0);
}
