/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:04:54 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/15 22:30:39 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include "token_list_functions.h"

int	quote_parsing2(t_token **token_list, char **str, char quote);
int	space_truncature(t_token *token_list);
int	new_token(t_token **list, char *str, int len, enum e_token type);

t_token *quote_parsing(char *str)
{
	int		i;
	t_token *token_list;
	
	token_list = NULL;
	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	str = &str[i];
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '"' && str[i] != '\'')
			i++;
		if (i != 0 && new_token(&token_list, str, i, EMPTY))
			return (NULL);
		if (!str[i])
			break ;
		str = &str[i];
		if ((*str == '"' || *str == '\'') && quote_parsing2(&token_list, &str, *str))
			return (NULL);
		i = 0;
	}
	if (space_truncature(token_list))
		return (NULL);
	return (token_list);
}

int	quote_parsing2(t_token **token_list, char **str, char quote)
{
	int		i;
	char	*str_quote;

	str_quote = *str;
	i = 1;
	while (str_quote[i] != quote) //CHECK : pas de protection ici pour le \0 mais les quotes sont toujours censees etre fermees;
		i++;
	i++;
	if (quote == '"' && new_token(token_list, str_quote, i, DQUOTE))
			return (1);
	else if (quote == '\'' && new_token(token_list, str_quote, i, QUOTE))
		return (1);
	*str = &str_quote[i];
	return (0);
}

int	space_truncature(t_token *token_list)
{
	char	*str_trunc;
	int		len;

	while (token_list)
	{
		if (token_list->token == EMPTY)
		{
			len = ft_strlen(token_list->str);
			if (token_list->prev && token_list->str[0] != ' ')
				token_list->prev->space_link = false;
			if (token_list->str[len - 1] != ' ')
				token_list->space_link = false;
			str_trunc = ft_strtrim(token_list->str, " ");
			if (!str_trunc)
			{
				// TODO : dprintf en sortie d'erreur d'une rreur de malloc
				ft_lstclear_token(&token_list);
				return (1);
			}
			free(token_list->str);
			token_list->str = str_trunc;
		}
		token_list = token_list->next;
	}
	return (0);
}

int	new_token(t_token **list, char *str, int len, enum e_token type)
{
	char	*instruction;
	t_token	*new;

	instruction = NULL;
	if (str)
	{	
		instruction = ft_strndup(str, len);
		if (!instruction)
		{	
			// TODO : dprintf en sortie d'erreur d'une rreur de malloc
			ft_lstclear_token(list);
			return(1);
		}
	}
	new = ft_lstnew_token(instruction, type);
	if (!new)
	{
		// TODO : dprintf en sortie d'erreur d'une rreur de malloc
		ft_lstclear_token(list);
		return(1);
	}
	ft_lstadd_back_token(list, new);
	return (0);
}
