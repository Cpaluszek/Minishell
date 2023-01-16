/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   central_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 20:03:00 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/16 19:34:02 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "token_list_functions.h"

int	central_parsing(t_global *shell, char *prompt)
{
	t_token	*token_list;

	get_input(shell, prompt);
	token_list = quote_parsing(shell->input);
	token_list = token_parsing(token_list);
	ft_lstadd_back_token(&shell->token_list, token_list);
	if (syntax_checking(shell))
		return ;
	if (uncompleted_line(shell))
		if (central_parsing(shell, ">"))
			return (1); // recursivite a mieux etudier
	add_history(shell->input);
	free(shell->input);
	return (0);
	//block_creation(shell); // in development =)
}

