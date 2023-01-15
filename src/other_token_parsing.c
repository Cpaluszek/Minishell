/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_token_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:39:52 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/15 13:20:46 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/structs.h"
#include "../Libft/headers/libft.h"


t_token	*central_parsing(char *str)
{
	t_token	*token_list;
	t_token	*temp;
	t_token	*splitted_token_list;

	token_list = quote_parsing(str);
	temp = token_list;
	while (temp )
	{
		if (temp->token == EMPTY)
		{
			splitted_token_list = other_token_parsing(temp ->str);
			if (temp->space_link == false)
				(ft_lstlast_token(splitted_token_list))->space_link = false;
			temp = temp->next;
			insert_token_list(temp->prev, splitted_token_list);
			ft_lstdelone(temp->prev);
		}
		else
			temp = temp->next;
	}
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
		str = &str[i];
		token = which_token(&str);
		other_token_parsing2(token_list, &str, token);
		i = 0;
	}
	return (token_list);
}

enum e_token which_token(char **str)
{
	if (**str == '>')
	{
		if (*(*str + 1) == '>')
		{
			*str = &str[2];
			return (OUTPUT_APPEND);
		}
		*str = &str[1];
		return (OUTPUT_TRUNC);	
	}
	else if (**str = '<')
	{
		if (*(*str + 1) == '<')
		{
			*str = &str[2];
			return (HERE_DOC);
		}
		*str = &str[1];
		return (INPUT);	
	}
	*str = &str[1];
	return (PIPE);
}
