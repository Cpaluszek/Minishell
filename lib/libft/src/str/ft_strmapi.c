/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:54:10 by cpalusze          #+#    #+#             */
/*   Updated: 2022/11/11 17:07:42 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*map;
	size_t	i;

	if (s == NULL)
		return (NULL);
	map = ft_strdup(s);
	if (map == NULL)
		return (NULL);
	i = 0;
	while (map[i])
	{
		map[i] = (*f)(i, map[i]);
		i++;
	}
	return (map);
}
