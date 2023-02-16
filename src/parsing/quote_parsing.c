/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:04:54 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/16 00:36:07 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token_list_functions.h"
#include "parsing.h"

static int	quote_parsing2(t_global *shell, char **str, char quote);
static int	is_a_dollar_token(char *str);
static void	new_token(t_global *shell, char *str, int len, enum e_token type);
static void	dollar_parsing(t_global *shell, char **str);

/**
 * @brief Parse Input with simple and double quote.
 * 
 * @param str The user input.
 * @return A chain list of token of 3 types (quote, double quote and normal).
 */
int	quote_parsing(t_global *shell, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '"' && str[i] != '\'' && \
			is_a_dollar_token(&str[i]) == false)
			i++;
		if (i != 0)
			new_token(shell, str, i, EMPTY);
		if (!str[i])
			break ;
		str = &str[i];
		if (*str == '$')
			dollar_parsing(shell, &str);
		else if (*str == '"' || *str == '\'')
			if (quote_parsing2(shell, &str, *str) == UNCOMPLETED)
				return (UNCOMPLETED);
		i = 0;
	}
	return (COMPLETED);
}

static int	quote_parsing2(t_global *shell, char **str, char quote)
{
	int		i;
	char	*str_quote;

	str_quote = *str;
	i = 1;
	while (str_quote[i] && str_quote[i] != quote)
		i++;
	if (!str_quote[i])
	{
		if (quote == '\'')
			shell->temp_prompt = "quote > ";
		else
			shell->temp_prompt = "dquote > ";
		return (UNCOMPLETED);
	}
	i++;
	if (quote == '"')
		new_token(shell, &str_quote[1], i - 2, DQUOTE);
	else if (quote == '\'')
		new_token(shell, &str_quote[1], i - 2, QUOTE);
	*str = &str_quote[i];
	return (COMPLETED);
}

static void	dollar_parsing(t_global *shell, char **str)
{
	char	*str_dollar;
	int		i;

	str_dollar = *str;
	i = 1;
	if (str_dollar[i] == '?')
	{
		new_token(shell, str_dollar, 2, DOLLAR);
		*str = &str_dollar[2];
		return ;
	}
	while (ft_isalnum(str_dollar[i]))
		i++;
	new_token(shell, str_dollar, i, DOLLAR);
	*str = &str_dollar[i];
}

static void	new_token(t_global *shell, char *str, int len, enum e_token type)
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

static int	is_a_dollar_token(char *str)
{
	char	c;

	c = *str;
	if (c != '$')
		return (false);
	c = str[1];
	if (c == '\0')
		return (false);
	if (c == '?')
		return (true);
	if (ft_isalnum(c))
		return (true);
	return (false);
}
