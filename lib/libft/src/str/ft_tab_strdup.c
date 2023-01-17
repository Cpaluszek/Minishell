/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_strdup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:07:44 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/01/17 14:39:51 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	**ft_tab_strdup(char **tab)
{
	int		i;
	int		size;
	char	**tab_dup;

	size = ft_size_tab(tab);
	tab_dup = malloc(sizeof(char *) * (size + 1));
	if (!tab_dup)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		tab_dup[i] = ft_strdup(tab[i]);
		if (!tab_dup[i])
			return (ft_free_split(tab_dup));
		i++;
	}
	tab_dup[i] = NULL;
	return (tab_dup);
}
