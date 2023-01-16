/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:10:18 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/15 23:41:42 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"

void	token_str_assignment(t_token *elem, enum e_token token);

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
	free(lst->str);
	free(lst);
}


void	ft_lstclear_token(t_token **lst)
{
	t_token	*p_lst;
	t_token	*p_del_lst;

	if (!lst)
		return ;
	p_lst = *lst;
	while (p_lst)
	{
		p_del_lst = p_lst;
		p_lst = p_lst->next;
		p_del_lst->next = NULL;
		ft_lstdelone_token(p_del_lst);
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

t_token	*ft_lstnew_token(char	*content, enum e_token token)
{
	t_token	*elem;

	elem = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!elem)
		return (NULL);
	elem->str = content;
	elem->cmd = NULL;
	elem->exit_status = 0;
	elem->space_link = true;
	elem->token = token;
	elem->next = NULL;
	elem->prev = NULL;
	token_str_assignment(elem, token);
	return (elem);
}

void	token_str_assignment(t_token *elem, enum e_token token)
{
	if (token == INPUT)
		elem->token_str = "<";
	else if (token == HERE_DOC)
		elem->token_str = "<<";
	else if (token == OUTPUT_TRUNC)
		elem->token_str = ">";
	else if (token == OUTPUT_APPEND)
		elem->token_str = ">>";
	else if (token == PIPE)
		elem->token_str = "|";
	else if (token == CMD)
		elem->token_str = "CMD";
	else if (token == DQUOTE)
		elem->token_str = "\"";
	else if (token == QUOTE)
		elem->token_str = "'";
	else if (token == DOLLAR)
		elem->token_str = "$";
	else if (token == NEW_LINE)
		elem->token_str = "newline";
}
