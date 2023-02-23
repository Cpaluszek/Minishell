/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:06:02 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/23 13:23:29 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

void	token_str_assignment(t_token *elem, enum e_token token);
void	token_str_assignment2(t_token *elem, enum e_token token);
int		origin_token_assignment(t_token *elem, char *str, enum e_token token);

t_token	*ft_lstnew_token(char *content, enum e_token token)
{
	t_token	*elem;

	elem = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!elem && content)
		free(content);
	if (!elem)
		return (NULL);
	token_str_assignment(elem, token);
	elem->origin_token_str = NULL;
	if (token >= CMD && token <= DOLLAR)
		if (origin_token_assignment(elem, content, token))
			return (NULL);
	elem->str = content;
	elem->cmd = NULL;
	elem->cmd_path = NULL;
	elem->exit_status = 0;
	elem->space_link = true;
	elem->token = token;
	elem->next = NULL;
	elem->prev = NULL;
	elem->fd_input = NULL;
	elem->fd_output = NULL;
	elem->ambiguous_redirect = false;
	return (elem);
}

int	origin_token_assignment(t_token *elem, char *str, enum e_token token)
{
	if (token == CMD || token == DOLLAR)
		elem->origin_token_str = ft_strdup(str);
	else
	{
		elem->origin_token_str = ft_strjoin(elem->token_str, str);
		if (!elem->origin_token_str)
		{
			free(elem);
			return (1);
		}
		elem->origin_token_str = ft_strjoin_and_free(elem->origin_token_str, \
			elem->token_str);
	}
	if (!elem->origin_token_str)
	{
		free(elem);
		return (1);
	}
	return (0);
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
	else if (token == AND)
		elem->token_str = "&&";
	else if (token == OR)
		elem->token_str = "||";
	else if (token == OPEN_PAR)
		elem->token_str = "(";
	else if (token == CLOSE_PAR)
		elem->token_str = ")";
	token_str_assignment2(elem, token);
}

void	token_str_assignment2(t_token *elem, enum e_token token)
{
	if (token == CMD)
		elem->token_str = "CMD";
	else if (token == DQUOTE)
		elem->token_str = "\"";
	else if (token == QUOTE)
		elem->token_str = "'";
	else if (token == DOLLAR)
		elem->token_str = "$";
	else if (token == NEW_LINE)
		elem->token_str = "newline";
	else if (token == EMPTY)
		elem->token_str = "SPC";
}
