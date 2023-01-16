/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:50:39 by cpalusze          #+#    #+#             */
/*   Updated: 2022/11/08 14:50:40 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *first, const char *second, size_t length)
{
	size_t	i;

	i = 0;
	while (i < length)
	{
		if (first[i] != second[i])
			return ((unsigned char)first[i] - (unsigned char)second[i]);
		if (!first[i] || !second[i])
			return (0);
		i++;
	}
	return (0);
}
