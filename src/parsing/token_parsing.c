/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:39:52 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/03 19:16:29 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token_list_functions.h"
#include "parsing.h"

static t_token		*create_sub_token_list(t_global *shell, char *str);
static enum e_token	which_token(char *str);
static int			new_token(t_token **token_list, char *str, \
int len, enum e_token type);
static void			setting_space_links_and_checking_parenthesis( \
t_global *shell, t_token *token_list);
void	setting_ambiguous_and_origin_str(t_global *shell, t_token *token_list, t_token *temp);

void	token_parsing(t_global *shell)
{
	t_token	*temp;
	t_token	*del;
	t_token	*splitted_token_list;

	temp = shell->token_list;
	while (temp)
	{
		if ((temp->token == EMPTY || temp->token == DOLLAR) && temp->str[0])
		{
			splitted_token_list = create_sub_token_list(shell, temp->str);
			if (temp->token == DOLLAR)
				setting_ambiguous_and_origin_str(shell, splitted_token_list, temp);
			insert_token_list(shell, temp, splitted_token_list);
			del = temp;
			temp = temp->next;
			ft_lstdelone_token(del);
		}
		else
			temp = temp->next;
	}
	setting_space_links_and_checking_parenthesis(shell, shell->token_list);
}

void	setting_ambiguous_and_origin_str(t_global *shell, t_token *token_list, t_token *temp)
{
		t_token	*token;
		int		i;

		token = token_list;
		free(token->origin_token_str);
		token->origin_token_str = ft_strdup(temp->origin_token_str);
		test_failed_malloc(shell, token->origin_token_str);
		i = 0;
		while (token)
		{
			if (token->token == CMD)
				i++;
			token = token->next;
		}
		if (i != 1)
			token_list->ambiguous_redirect = true;
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
		while (str[i] && (!ft_is_inside(str[i], "<>|() ") && \
			ft_strncmp(&str[i], "&&", 2)))
			i++;
		if (i != 0 && new_token(&token_list, str, i, CMD))
			error_exit_shell(shell, ERR_MALLOC);
		if (!str[i])
			break ;
		token = which_token(&str[i]);
		i++;
		if (token == HERE_DOC || token == 3 || token == AND || token == OR)
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
	return (EMPTY);
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

static void	setting_space_links_and_checking_parenthesis(t_global *shell, \
	t_token *token)
{
	shell->nb_open_parenthesis = 0;
	while (token)
	{
		if (token->token != EMPTY)
			if (token->next && token->next->token != EMPTY)
			token->space_link = false;
		if (token->token == OPEN_PAR || token->token == CLOSE_PAR)
			shell->nb_open_parenthesis += 8 - token->token;
		token = token->next;
	}
	if (shell->nb_open_parenthesis > 0)
		shell->command_line = UNFINISHED_PARENTHESIS;
	else if (shell->command_line != UNFINISHED_QUOTE)
		shell->command_line = FINISHED_PARENTHESIS;
}
