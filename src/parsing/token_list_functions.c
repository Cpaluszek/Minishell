/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:10:18 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/17 13:45:57 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_token(t_token **lst, t_token *new)
{
	t_token	*p_lst;

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

void	ft_lstdelone_token(t_token *lst)
{
	if (!lst)
		return ;
	ft_free_split(lst->cmd);
	ft_free(lst->cmd_path);
	ft_free(lst->origin_token_str);
	free(lst->str);
	free(lst);
}

void	ft_lstclear_token(t_token **lst)
{
	t_token	*p_lst;
	t_token	*p_del_lst;

	if (!lst || !(*lst))
		return ;
	p_lst = *lst;
	while (p_lst)
	{
		p_del_lst = p_lst;
		p_lst = p_lst->next;
		p_del_lst->next = NULL;
		p_del_lst->prev = NULL;
		ft_lstdelone_token(p_del_lst);
		p_del_lst = NULL;
	}
	*lst = NULL;
}

t_token	*ft_lstlast_token(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
