/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:08:20 by cpalusze          #+#    #+#             */
/*   Updated: 2022/11/11 17:10:32 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_striteri(char *s, char (*f)(unsigned int, char*))
{
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
	return (s);
}
