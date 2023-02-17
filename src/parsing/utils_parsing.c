/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:49:00 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/02/17 13:40:54 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "token_list_functions.h"

// TODO : CHECK LINE INPUT < 100000 on est pas des fous non plus
void	get_input(t_global *shell, char *prompt)
{
	char	*input;

	input = NULL;
	while (1)
	{
		ft_free(input);
		input = readline(prompt);
		if (input == NULL)
			exit_shell_from_signal(shell);
		if (not_only_spaces(input) == -1 && ft_strlen(input) && \
			shell->command_line == BEGIN)
			add_history(input);
		if ((ft_strlen(input) && not_only_spaces(input) >= 0))
			break ;
	}
	ft_free(shell->input);
	shell->input = input;
	shell->input_completed = ft_strjoin_and_free(shell->input_completed, input);
	test_failed_malloc(shell, shell->input_completed);
}

int	not_only_spaces(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (line[i] != ' ')
			return (i);
	if (line[i] == '\n')
		return (i);
	return (-1);
}

void	test_failed_malloc(t_global *shell, void *content)
{
	if (!content)
		error_exit_shell(shell, ERR_MALLOC);
}

void	remove_token(t_token *token)
{
	if (!token)
		return ;
	if (token->prev)
		token->prev->next = token->next;
	if (token->next)
		token->next->prev = token->prev;
	ft_lstdelone_token(token);
}

void	insert_token_list(t_token **head_list, t_token *token, \
t_token *splitted_token_list)
{
	t_token	*last_splitted_token;

	last_splitted_token = ft_lstlast_token(splitted_token_list);
	last_splitted_token->next = token->next;
	if (token->next)
		token->next->prev = last_splitted_token;
	last_splitted_token->space_link = token->space_link;
	if (token->prev)
	{
		token->prev->next = splitted_token_list;
		splitted_token_list->prev = token->prev;
	}
	else
		*head_list = splitted_token_list;
}
