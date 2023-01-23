/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:39:52 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/23 11:35:01 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include "token_list_functions.h"
#include "parsing.h"

void			insert_token_list(t_token *token_list, t_token *splitted_token_list);
t_token			*create_sub_token_list(char *str);
enum e_token	which_token(char *str);

t_token	*token_parsing(t_token *token_list)
{
	t_token	*temp;
	t_token	*del;
	t_token	*splitted_token_list;

	temp = token_list;
	while (temp)
	{
		if (temp->token == EMPTY && temp->str[0])
		{
			splitted_token_list = create_sub_token_list(temp->str);// ajouter une fonction de protection de malloc
			insert_token_list(temp, splitted_token_list);
			del = temp;
			temp = temp->next;
			ft_lstdelone_token(del);
			token_list = splitted_token_list;
		}
		else
			temp = temp->next;
	}
	while (token_list->prev)
		token_list = token_list->prev;
	return (token_list);
}

t_token	*create_sub_token_list(char *str)
{
	int				i;
	enum e_token	token;
	t_token			*token_list;

	token_list = NULL;
	i = not_only_spaces(str);
	while (str[i])
	{
		while (str[i] && !ft_is_inside(str[i], "<>|\n"))
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
	else if (*str == '|')
		return (PIPE);
	return (NEW_LINE);
}

void	insert_token_list(t_token *token_list, t_token *splitted_token_list)
{
	t_token	*last_splitted_token;

	if (token_list->prev)
	{
		token_list->prev->next = splitted_token_list;
		splitted_token_list->prev = token_list->prev;
	}
	last_splitted_token = ft_lstlast_token(splitted_token_list);
	last_splitted_token->next = token_list->next;
	if (token_list->next)
		token_list->next->prev = last_splitted_token;
	last_splitted_token->space_link = token_list->space_link;
}
