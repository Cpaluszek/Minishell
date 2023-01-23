/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:41:19 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/21 17:18:38 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	**ft_free_split(char **strs)
{
	int	i;

	if (!strs)
		return (NULL);
	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
	strs = NULL;
	return (NULL);
}
