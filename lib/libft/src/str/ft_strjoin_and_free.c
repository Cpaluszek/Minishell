/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_and_free.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:41:20 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/09 14:49:20 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief allocates (with malloc(3)) and returns a string ending with ’\0’,
 * result of the concatenation of s1 and s2.
 * s1 will be freed after calling ft_strjoin
 * 
 * @param s1 The prefix string - will be freed
 * @param s2 The sufix string
 * @return the new string, NULL if the allocation fails
 */
char	*ft_strjoin_and_free(char *s1, const char *s2)
{
	char	*join;

	join = ft_strjoin(s1, s2);
	if (s1 != NULL)
		free(s1);
	return (join);
}
