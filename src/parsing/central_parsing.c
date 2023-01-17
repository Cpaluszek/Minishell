/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   central_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 20:03:00 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/17 20:16:15 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "token_list_functions.h"

int	uncompleted_line(t_token *token_list);
void	token_dollar_expand_and_str_merging(t_global *shell);

int	central_parsing(t_global *shell, char *prompt)
{
	t_token	*token_list;

	if (shell->command_line == SYNTAX_ERROR)
		return (1);
	if (shell->command_line ==  COMPLETED)
		return (0);
	get_input(shell, prompt);
	token_list = quote_parsing(shell->input);
	token_list = token_parsing(token_list);
	ft_lstadd_back_token(&shell->token_list, token_list);
	printf("\n\n");
	if (syntax_checking(shell))
		return (1);
	if (uncompleted_line(shell->token_list))
		central_parsing(shell, ">");
	if (shell->command_line == UNCOMPLETED)
	{
		shell->command_line = COMPLETED;
		add_history(shell->input_completed);
		// token_dollar_expand_and_str_merging(shell);
		add_path_to_command_token(shell);
		ft_lstadd_back_block(&shell->block_list, ft_lstnew_block(shell->token_list));
	}
	return (0);
}

int	uncompleted_line(t_token *token_list)
{
	t_token *last_token;

	last_token = ft_lstlast_token(token_list);
	if (last_token->token == PIPE || last_token->token == AND \
		|| last_token->token == OR)
		return (1);
	return (0);
}
