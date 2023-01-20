/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:28:05 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/20 21:31:09 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	swap_lst_content(void *first, void *second);

void	ft_lstsort(t_list **lst, int (*cmp)())
{
	int		i;
	int		j;
	int		size;
	t_list	*current;

	size = ft_lstsize(*lst);
	i = 0;
	while (i < size)
	{
		j = 0;
		current = *lst;
		while (j < size - 1 - i)
		{
			if ((*cmp)(current->content, current->next->content) > 0)
				swap_lst_content(current->content, current->next->content);
			current = current->next;
			j++;
		}
		i++;
	}
}

static void	swap_lst_content(void *first, void *second)
{
	void	*temp;

	temp = first;
	first = second;
	second = temp;
}
