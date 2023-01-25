/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:05:26 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/25 10:37:15 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	tab_copy(char **dest, char **src, int len);

/**
 * @brief allocates (with malloc(3)) and returns a tab ending with NULL,
 * result of the merging of tab1 and tab2.
 * tab1 will be freed.
 * 
 * @param tab1 The first tab - will be freed
 * @param tab2 The second tab.
 * @return the new tab, NULL if the allocation fails
 */
char	**ft_merge_tab(char **tab1, char **tab2)
{
	char	**merged_tab;
	int		i;
	int		j;
	int		size_tab1;
	int		size_tab2;

	size_tab1 = ft_size_tab(tab1);
	size_tab2 = ft_size_tab(tab2);
	merged_tab = malloc(sizeof(char *) * (size_tab1 + size_tab2 + 1));
	if (!merged_tab)
		return (NULL);
	if (tab_copy(merged_tab, tab1, 0))
		return (NULL);
	if (tab_copy(merged_tab, tab2, size_tab2))
		return (NULL);
	ft_free_split(tab1);
	return (merged_tab);
}


static int	tab_copy(char **dest, char **src, int len)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[len + i] = ft_strdup(src[i]);
		if (!dest[len + i])
		{
			(ft_free_split(dest));
			return (1);
		}
		i++;
	}
	dest[len + i] = NULL;
	return (0);
}