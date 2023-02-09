/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 23:20:20 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/08 23:01:42 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "token_list_functions.h"

//NOTE : garder les token->prev pour exit dun fail malloc?
static t_block	*create_sub_block(t_global *shell, t_token **first_token, \
	t_block *upper_block);
void	add_redirection_for_upper_block(t_block *upper_block, t_token *token, \
t_token **first_token);

t_block	*block_parsing(t_global *shell, t_block *upper_block, t_token *first_token)
{
	t_token	*token;
	t_block *first_block;
	t_block	*new_block;
	t_block	*sub_block;

	first_block = NULL;
	token = first_token;
	while (token)
	{
		if (token->token == OPEN_PAR)
		{
			new_block = ft_lstnew_block(upper_block, NULL);
			test_failed_malloc(shell, new_block);
			sub_block = create_sub_block(shell, &token, new_block);
			new_block->sub_block = sub_block;
		// add_link(new_block, token->next);
			ft_lstadd_back_block(&first_block, new_block);
		}
		else
		{
			first_token = token; // a voir si a enlever
			while (token && (token->token > CLOSE_PAR || token->token <= PIPE))
			{
				if (token->next && token->next->token == OPEN_PAR)
					break ; // dans les cas ou une parenthese suit un pipe	
				token = token->next;
			}
			if (token)
				token->prev->next = NULL;
			// penser a modifier le set fd to token cmd pour integrer les nouveaux file descriptors
			new_block = ft_lstnew_block(upper_block, first_token);
			test_failed_malloc(shell, new_block);
			// add_link(new_block, token);
			// token->prev = NULL;
			//set_block_fd_to_command_token;
			if (token && token->next)
			{
				token = token->next;
				ft_lstdelone_token(token->prev);
			}
			else
			{
				ft_lstdelone_token(token);
				token = NULL;
			}
			ft_lstadd_back_block(&first_block, new_block);
			// pour les fails de malloc
		}
	}
	return (first_block);
}

static t_block	*create_sub_block(t_global *shell, t_token **first_token, \
	t_block *upper_block)
{
	t_token	*token;
	t_token	*begin_of_token_list;
	t_block	*first_sub_block;
	int		nb_parenthesis;

	nb_parenthesis = 1;
	token = (*first_token)->next;
	begin_of_token_list = token;
	ft_lstdelone_token(begin_of_token_list->prev);
	begin_of_token_list->prev = NULL;
	while (nb_parenthesis)
	{
		if (token->token == CLOSE_PAR || token->token == OPEN_PAR)
			nb_parenthesis += 8 - token->token;
		if (nb_parenthesis)
			token = token->next;
		dprintf(1, "nb of parenthesis : %d\n", nb_parenthesis);
	}
	dprintf(1, "\n\n");
	token->prev->next = NULL;
	token = token->next;
	if (token)
		ft_lstdelone_token(token->prev); // si ce nest pas le dernier token
	if (token)
		token->prev = NULL;
	add_redirection_for_upper_block(upper_block, token, first_token);
	if (*first_token)
		(*first_token = (*first_token)->next);
	// add_link_between_blocks(upper_block, *first_token);
	// del firstoken et frst token = firstoken next attention si dernier token
	first_sub_block = block_parsing(shell, upper_block, begin_of_token_list);
	test_failed_malloc(shell, first_sub_block);
	return (first_sub_block);
}

void	add_redirection_for_upper_block(t_block *upper_block, t_token *token, \
t_token **first_token)
{
	int		*fd_input;
	int		*fd_output;

	fd_input = NULL;
	fd_output = NULL;
	if (token && token->token <= OUTPUT_APPEND)
		upper_block->redirection_token_list = token;
	while (token && token->token <= OUTPUT_APPEND)
	{
		if (token->token <= HERE_DOC)
			fd_input = &token->fd_file;
		else if (token->token <= OUTPUT_APPEND)
			fd_output = &token->fd_file;
		token = token->next;
	}
	if (token && token->prev)
		token->prev->next = NULL;
	if (fd_input)
		upper_block->fd_input = fd_input;
	if (fd_output)
		upper_block->fd_output = fd_output;
	*first_token = token;
	// shell->token_list = token; // pour les fails de mallocs;
}

void	add_link_between_blocks(t_block *block, t_token *token)
{
	if (token->token == AND)
		block->logical_link = AND_LINK;
	else if (token->token == OR)
		block->logical_link = OR_LINK;
	else if (token->token == PIPE)
	{
		block->logical_link = PIPE_LINK;
		block->make_a_pipe = true;
		if (!block->fd_output)
			block->fd_output = &block->pipe_fd[1];
	}
	if (block->prev && block->prev->logical_link == PIPE_LINK)
	{
		block->previous_block_pipe_fd0 = &block->prev->pipe_fd[0];
		if (!block->fd_input)
			block->fd_input = block->previous_block_pipe_fd0;
	}
}
