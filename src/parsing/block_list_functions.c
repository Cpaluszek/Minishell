/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_list_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:10:18 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/15 10:12:30 by jlitaudo         ###   ########.fr       */
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
		new->prev = p_lst;
	}
}

void	ft_lstdelone_block(t_block *lst)
{
	if (!lst)
		return ;
	ft_lstclear_token(&lst->token_list);
	ft_lstclear_token(&lst->redirection_token_list);
	lst->token_list = NULL;
	lst->redirection_token_list = NULL;
	free(lst);
}

void	ft_lstclear_block(t_block **first_block)
{
	t_block	*block;
	t_block	*del_block;

	if (!first_block || !(*first_block))
		return ;
	block = *first_block;
	while (block)
	{
		if (block->sub_block)
			ft_lstclear_block(&block->sub_block);
		del_block = block;
		block = block->next;
		del_block->next = NULL;
		del_block->prev = NULL;
		ft_lstdelone_block(del_block);
	}
	*first_block = NULL;
}

t_block	*ft_lstlast_block(t_block *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_block	*ft_lstnew_block(t_block *upper_block, t_token *token_list)
{
	t_block	*elem;

	elem = (t_block *)ft_calloc(1, sizeof(t_block));
	if (!elem)
		return (NULL);
	elem->next = NULL;
	elem->prev = NULL;
	elem->sub_block = NULL;
	elem->upper_block = upper_block;
	elem->token_list = token_list;
	elem->redirection_token_list = NULL;
	elem->fd_input = NULL;
	elem->fd_output = NULL;
	elem->make_a_pipe = false;
	elem->block_level = 0;
	elem->fd_input_level = 0;
	elem->fd_output_level = 0;
	if (upper_block)
		elem->block_level = upper_block->block_level + 1;
	elem->logical_link = NO_LINK;
	return (elem);
}
