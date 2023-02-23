/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_all_heredocs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:53:37 by jlitaudo          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/02/20 14:25:41 by jlitaudo         ###   ########.fr       */
=======
/*   Updated: 2023/02/21 09:39:59 by Teiki            ###   ########.fr       */
>>>>>>> c21f1c66cd386ca3222eeb0128b9e340507c6b7d
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <unistd.h>

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
		if (token->space_link == true)
			break ;
		here_doc->str = ft_strjoin_and_free(here_doc->str, token->str);
		test_failed_malloc(shell, here_doc->str);
		temp = token;
		token = token->next;
		remove_token(temp);
	}
	return (token);
}
