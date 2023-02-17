/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_all_heredocs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:53:37 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/02/17 10:49:17 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void		merge_heredoc_redirection(t_global *shell, t_token *token);
static t_token	*merge_linked_token(t_global *shell, t_token *here_doc);

int	fill_all_heredocs(t_global *shell)
{
	t_token	*token;

	token = shell->token_list;
	merge_heredoc_redirection(shell, token);
	while (token)
	{
		if (token->token == HERE_DOC)
		{
			if (make_pipe_heredoc(shell, token))
			{
				shell->command_line = HERE_DOC_PROBLEM;
				return (EXIT_FAILURE);
			}
			add_fd_to_list(shell, &token->pipe_fd[0]);
		}
		token = token->next;
	}
	return (EXIT_SUCCESS);
}

static void	merge_heredoc_redirection(t_global *shell, t_token *token)
{
	while (token)
	{
		if (token->token == HERE_DOC && token->next)
			token = merge_linked_token(shell, token);
		else
			token = token->next;
	}
}

static t_token	*merge_linked_token(t_global *shell, t_token *here_doc)
{
	t_token	*token;
	t_token	*temp;

	token = here_doc->next;
	here_doc->str = ft_strdup(token->str);
	test_failed_malloc(shell, here_doc->str);
	temp = token;
	token = token->next;
	remove_token(temp);
	while (token && token->token >= CMD)
	{
		here_doc->str = ft_strjoin_and_free(here_doc->str, token->str);
		test_failed_malloc(shell, here_doc->str);
		temp = token;
		token = token->next;
		remove_token(temp);
		if (!token || token->space_link == true)
			break ;
	}
	return (token);
}
