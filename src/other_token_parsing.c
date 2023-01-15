/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_token_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:39:52 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/15 19:40:59 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include "token_list_functions.h"
#include "parsing.h"
#include <stdio.h>

void			insert_token_list(t_token *token_list, t_token *splitted_token_list);
t_token			*other_token_parsing(char *str);
enum e_token	which_token(char *str);

t_token	*central_parsing(char *str)
{
	t_token	*token_list;
	t_token	*temp;
	t_token	*del;
	t_token	*splitted_token_list;

	token_list = quote_parsing(str);
	temp = token_list;
	while (temp)
	{
		if (temp->token == EMPTY)
		{
			splitted_token_list = other_token_parsing(temp->str); // ajouter une fonction de protection de malloc
			if (temp->space_link == false)
				(ft_lstlast_token(splitted_token_list))->space_link = false;
			insert_token_list(temp, splitted_token_list);
			del = temp;
			temp = temp->next;
			ft_lstdelone_token(del);
		}
		else
			temp = temp->next;
	}
	while (token_list->prev)
		token_list = token_list->prev;
	return (token_list);
}

void	insert_token_list(t_token *token_list, t_token *splitted_token_list)
{
	t_token *last_splitted_token;

	if (token_list->prev)
	{
		token_list->prev->next = splitted_token_list;
		splitted_token_list->prev = token_list->prev;
	}
	last_splitted_token = ft_lstlast_token(splitted_token_list);
	last_splitted_token->next = token_list->next;
	if (token_list->next)
		token_list->next->prev = last_splitted_token;
}

t_token	*other_token_parsing(char *str)
{
	int				i;
	enum e_token	token;
	t_token			*token_list;


	token_list = NULL;
	i = 0;
	while (str[i])
	{
		while (str[i] && !ft_is_inside(str[i], "<>|"))
			i++;
		if (i != 0 && new_token(&token_list, str, i, CMD))
			return (NULL);
		if (!str[i])
			break ;
		token = which_token(&str[i]);
		i++;
		if (token == HERE_DOC || token == OUTPUT_APPEND)
			i++;
		if (new_token(&token_list, NULL, 0, token))
			return (NULL);
		str = &str[i];
		i = 0;
	}
	return (token_list);
}

enum e_token which_token(char *str)
{
	if (*str == '>')
	{
		if (str[1] && str[1] == '>')
			return (OUTPUT_APPEND);
		return (OUTPUT_TRUNC);	
	}
	else if (*str == '<')
	{
		if (str[1] && str[1] == '<')
			return (HERE_DOC);
		return (INPUT);	
	}
	return (PIPE);
}
