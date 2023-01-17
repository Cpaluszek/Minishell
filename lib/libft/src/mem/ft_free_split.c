/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:41:19 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/17 11:19:15 by jlitaudo         ###   ########.fr       */
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
	return (NULL);
}
