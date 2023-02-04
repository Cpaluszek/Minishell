/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_and_free_s2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:41:20 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/03 13:43:38 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief allocates (with malloc(3)) and returns a string ending with ’\0’,
 * result of the concatenation of s1 and s2.
 * s2 will be freed after calling ft_strjoin
 * 
 * @param s1 The prefix string
 * @param s2 The sufix string - will be freed
 * @return the new string, NULL if the allocation fails
 */
char	*ft_strjoin_and_free_s2(char *s1, char *s2)
{
	char	*join;

	join = ft_strjoin(s1, s2);
	if (s2 != NULL)
		free(s2);
	return (join);
}
