/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   central_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 20:03:00 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/15 23:32:51 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "token_list_functions.h"
#include "parsing.h"
# include <stdio.h>

void	empty_token_assignation(t_token *token);
int		syntaxe_checking(t_token *token);
void	remove_empty_token(t_token **token_list);

t_token	*central_parsing(char *str)
{
	t_token	*token_list;
	
	token_list = quote_parsing(str);
	token_list = token_parsing(token_list);
	empty_token_assignation(token_list);
	if (syntaxe_checking(token_list))
		return (NULL);

	return (token_list);
}

void	empty_token_assignation(t_token *token)
{
	int	i;

	while(token)
	{
		if (token->token == CMD)
		{
			i = 0;
			while (token->str[i] == ' ')
				i++;
			if (!token->str[i])
				token->token = EMPTY;
		}
		token = token->next;
	}
}

int	syntaxe_checking(t_token *token_list)
{
	t_token	*token;
	
	token = token_list;
	while (token)
	{
		if (token->token == 2)
			if (token->next && token->next->token == 9)
				if (token->next->next && token->next->next->token == 5)
				{
					dprintf(2, "%s`%s'\n", ERR_SYNTAX, "|");
					return (1);
				}
		token = token->next;
	}
	remove_empty_token(&token_list);
	token = token_list;
	while (token)
	{
		if (token->token <= 4 && token->next && 
			(token->next->token <= 4 || token->next->token == 10))
		{
			dprintf(2, "%s`%s'\n", ERR_SYNTAX, token->next->token_str);
			return (1);
		}
		token = token->next;
	}
	return (0);
}

void	remove_empty_token(t_token **token_list)
{
	t_token	*token;
	t_token	*temp;

	token = *token_list;
	if (token->token == EMPTY)
	{
		temp = token;
		token = token->next;
		token->prev = NULL;
		ft_lstdelone_token(temp);
		*token_list = token;
	}
	while (token)
	{
		if (token->token == EMPTY)
		{
			temp = token;
			token = token->next;
			token->prev = temp->prev;
			temp->prev->next = token;
			ft_lstdelone_token(temp);
		}
		else
			token = token->next;
	}
}