/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:48:04 by cpalusze          #+#    #+#             */
/*   Updated: 2022/11/08 14:48:06 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_elem;

	last_elem = *lst;
	while (last_elem && last_elem->next)
		last_elem = last_elem->next;
	if (last_elem)
		last_elem->next = new;
	else
		*lst = new;
}
