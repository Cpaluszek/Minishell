/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:39:52 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/29 23:58:46 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token_list_functions.h"
#include "parsing.h"

static t_token		*create_sub_token_list(t_global *shell, char *str);
static enum e_token	which_token(char *str);
static int			new_token(t_token **token_list, char *str, \
int len, enum e_token type);

void	token_parsing(t_global *shell)
{
	t_token	*temp;
	t_token	*del;
	t_token	*splitted_token_list;

	temp = shell->token_list;
	while (temp)
	{
		if (temp->token == EMPTY && temp->str[0])
		{
			splitted_token_list = create_sub_token_list(shell, temp->str);
			insert_token_list(shell, temp, splitted_token_list);
			del = temp;
			temp = temp->next;
			ft_lstdelone_token(del);
		}
		else
			temp = temp->next;
	}
}

static t_token	*create_sub_token_list(t_global *shell, char *str)
{
	int				i;
	enum e_token	token;
	t_token			*token_list;

	token_list = NULL;
	i = 0;
	while (str[i])
	{
		while (str[i] && !ft_is_inside(str[i], "<>|&()\n"))
			i++;
		if (i != 0 && new_token(&token_list, str, i, CMD))
			error_exit_shell(shell, ERR_MALLOC);
		if (!str[i])
			break ;
		token = which_token(&str[i]);
		i++;
		if (token == HERE_DOC || token == OUTPUT_APPEND)
			i++;
		if (new_token(&token_list, NULL, 0, token))
			error_exit_shell(shell, ERR_MALLOC);
		str = &str[i];
		i = 0;
	}
	return (token_list);
}

static enum e_token	which_token(char *str)
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
	else if (*str == '|' && str[1] && str[1] == '|')
		return (OR);
	else if (*str == '|')
		return (PIPE);
	else if (*str == '&' && str[1] && str[1] == '&')
		return (AND);
	else if (*str == '(')
		return (OPEN_PAR);
	else if (*str == ')')
		return (CLOSE_PAR);
	return (NEW_LINE);
}

static int	new_token(t_token **token_list, char *str, \
int len, enum e_token type)
{
	char	*instruction;
	t_token	*new;

	instruction = NULL;
	if (str)
	{	
		instruction = ft_strndup(str, len);
		if (!instruction)
		{
			ft_lstclear_token(token_list);
			return (1);
		}
	}
	new = ft_lstnew_token(instruction, type);
	if (!new)
	{
		ft_lstclear_token(token_list);
		return (1);
	}
	ft_lstadd_back_token(token_list, new);
	return (0);
}
