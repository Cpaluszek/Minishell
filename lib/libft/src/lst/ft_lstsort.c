/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:28:05 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/20 21:36:02 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstsort(t_list **lst, int (*cmp)())
{
	int		i;
	int		j;
	int		size;
	t_list	*current;
	void	*temp;

	size = ft_lstsize(*lst);
	i = 0;
	while (i < size)
	{
		j = 0;
		current = *lst;
		while (j < size - 1 - i)
		{
			if ((*cmp)(current->content, current->next->content) > 0)
			{
				temp = current->content;
				current->content = current->next->content;
				current->next->content = temp;
			}
			current = current->next;
			j++;
		}
		i++;
	}
}
