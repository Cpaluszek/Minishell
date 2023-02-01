/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_list_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:10:18 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/31 23:38:12 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token_list_functions.h"

void	ft_lstadd_back_block(t_block **lst, t_block *new)
{
	t_block	*p_lst;

	if (!lst)
		return ;
	if (!(*lst))
	{
		if (new)
			*lst = new;
		return ;
	}
	if (new)
	{
		p_lst = *lst;
		while (p_lst->next)
			p_lst = p_lst->next;
		p_lst->next = new;
	}
}

void	ft_lstdelone_block(t_block *lst)
{
	if (!lst)
		return ;
	ft_lstclear_token(&lst->token_list);
	lst->token_list = NULL;
	free(lst);
}


void	ft_lstclear_block(t_block **lst)
{
	t_block	*p_lst;
	t_block	*p_del_lst;

	if (!lst)
		return ;
	p_lst = *lst;
	while (p_lst)
	{
		p_del_lst = p_lst;
		p_lst = p_lst->next;
		p_del_lst->next = NULL;
		ft_lstdelone_block(p_del_lst);
	}
	*lst = NULL;
}

t_block	*ft_lstlast_block(t_block *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_block	*ft_lstnew_block(t_token *token_list, enum e_link link)
{
	t_block	*elem;

	elem = (t_block *)ft_calloc(1, sizeof(t_block));
	if (!elem)
		return (NULL);
	elem->next = NULL;
	elem->sub_block = NULL;
	elem->upper_block = NULL;
	elem->token_list = token_list;
	elem->logical_link = link;
	return (elem);
}
