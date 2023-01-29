/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:04:54 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/29 18:31:21 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token_list_functions.h"
#include "parsing.h"

static void	quote_parsing2(t_global *shell, char **str, char quote);
static void	setting_space_links(t_token *token_list);

/**
 * @brief Parse Input with simple and double quote.
 * 
 * @param str The user input.
 * @return A chain list of token of 3 types (quote, double quote and normal).
 */
void	quote_parsing(t_global *shell, char *str)
{
	int		i;

	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		while (str[i] && str[i] != '"' && str[i] != '\'')
			i++;
		if (i != 0)
			new_token(shell, str, i, EMPTY);
		if (!str[i])
			break ;
		str = &str[i];
		if (*str == '"' || *str == '\'')
			quote_parsing2(shell, &str, *str);
		i = 0;
	}
	setting_space_links(shell->token_list);
}

static void	quote_parsing2(t_global *shell, char **str, char quote)
{
	int		i;
	char	*str_quote;

	str_quote = *str;
	i = 1;
	while (str_quote[i] != quote) //CHECK : pas de protection ici pour le \0 mais les quotes sont toujours censees etre fermees;
		i++;
	i++;
	if (quote == '"')
		new_token(shell, &str_quote[1], i - 2, DQUOTE);
	else if (quote == '\'')
		new_token(shell, &str_quote[1], i - 2, QUOTE);
	*str = &str_quote[i];
}

static void	setting_space_links(t_token *token_list)
{
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
		}
		else if (token_list->next && token_list->next->token != EMPTY)
			token_list->space_link = false;
		token_list = token_list->next;
	}
}

void	new_token(t_global *shell, char *str, int len, enum e_token type)
{
	char	*instruction;
	t_token	*new;

	instruction = NULL;
	if (str)
	{	
		instruction = ft_strndup(str, len);
		test_failed_malloc(shell, instruction);
	}
	new = ft_lstnew_token(instruction, type);
	test_failed_malloc(shell, new);
	ft_lstadd_back_token(&shell->token_list, new);
}
