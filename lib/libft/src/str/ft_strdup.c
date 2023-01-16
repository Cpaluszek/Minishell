/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:49:38 by cpalusze          #+#    #+#             */
/*   Updated: 2022/11/08 14:49:39 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	len;
	size_t	i;
	char	*copy;

	i = 0;
	len = ft_strlen(str);
	copy = malloc(sizeof(char) * len + 1);
	if (copy == NULL)
		return (NULL);
	while (i < len)
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = 0;
	return (copy);
}
