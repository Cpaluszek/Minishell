/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merging_str_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:54:42 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/01/29 00:06:24 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "token_list_functions.h"
#include "libft.h"

static void	merge_command(t_global *shell, t_token *token_list);
static void	merge_redirection(t_global *shell, t_token *token_list);
static void	joining_with_space_truncature(t_global *shell, \
t_token *token, char **redirection_str);
void	remove_token(t_token *token);

void	token_merging(t_global *shell)
{
	t_token	*token;

	token = shell->token_list;
	while (token)
	{
		if (token->token <= 3)
			merge_redirection(shell, token);
		token = token->next;
	}
	token = shell->token_list;
	// printf("OK!\n");
	// print_command_line(token);
	// printf("OK2!\n");
	empty_token_assignation(token); // checker si premier elem est une commande que ca ne fait pas de byug
	while (token)
	{
		if (token->token == CMD)
		{
			token->cmd = ft_split(token->str, ' ');
			test_failed_malloc(shell, token->cmd);
		}
		else if (token->token == QUOTE || token->token == DQUOTE)
		{
			token->cmd = ft_split(token->str, '\0');
			test_failed_malloc(shell, token->cmd);
			token->token = CMD;
		}
		token = token->next;
	}
	print_command_line(token);
	token = shell->token_list;
	while (token)
	{
		if (token->token == CMD)
			merge_command(shell, token);
		token = token->next;
	}
}
static void	merge_command(t_global *shell, t_token *first_cmd)
{
	t_token	*token;
	t_token	*temp;

	token = first_cmd->next;;
	while (token && token->token != PIPE)
	{
		if (token->token == CMD || token->token == QUOTE || \
			token->token == DQUOTE)
		{
			first_cmd->cmd = ft_merge_tab(first_cmd->cmd, token->cmd);
			test_failed_malloc(shell, first_cmd->cmd);
			temp = token;
			token = token->next;
			remove_token(temp);
		}
		else
			token = token->next;
	}
}

// static void	merge_command(t_global *shell, t_token *token_list)
// {
// 	t_token	*token;
// 	t_token	*temp;
// 	char	*str;

// 	str = token_list->str;
// 	token = token_list->next;
// 	while (token && token->token != PIPE)
// 	{
// 		if (token->token == CMD || token->token == QUOTE || \
// 			token->token == DQUOTE)
// 		{
// 			str = ft_strjoin_and_free(str, token->str);
// 			test_failed_malloc(shell, str);
// 			temp = token;
// 			token = token->next;
// 			remove_token(temp);
// 		}
// 		else
// 			token = token->next;
// 	}
// 	token_list->str = str;
// }

static void	merge_redirection(t_global *shell, t_token *token_list)
{
	t_token	*token;
	t_token	*temp;
	char	*str;
	bool	space_link;

	str = token_list->str;
	token = token_list->next;
	while (token && token->token > PIPE)
	{
		space_link = token->space_link;
		temp = token;
		token = token->next;
		if (temp->token == CMD)
			joining_with_space_truncature(shell, temp, &str);
		if (temp->token == CMD && ft_strlen(temp->str))
			break ;
		if (temp->token == QUOTE || temp->token == DQUOTE)
		{
			str = ft_strjoin_and_free(str, temp->str);
			test_failed_malloc(shell, str);
			remove_token(temp);
		}
		if (space_link == true)
			break ;
	}
	token_list->str = str;
}

static void	joining_with_space_truncature(t_global *shell, \
t_token *token, char **redirection_str)
{
	char	*token_str;
	char	*new_str;
	int		i;
	int		j;

	token_str = token->str;
	i = 0;
	j = 0;
	while (token_str[i] && token_str[i] == ' ')
		i++;
	while (token_str[i + j] && token_str[i + j] != ' ')
		j++;
	new_str = ft_substr(token_str, i, j);
	test_failed_malloc(shell, new_str);
	*redirection_str = ft_strjoin_and_free(*redirection_str, new_str);
	test_failed_malloc(shell, *redirection_str);
	free(new_str);
	new_str = ft_substr(token_str, j + i, ft_strlen(token->str));
	test_failed_malloc(shell, new_str);
	free(token_str);
	token->str = new_str;
}

void	remove_token(t_token *token)
{
	if (token->prev)
		token->prev->next = token->next;
	if (token->next)
		token->next->prev = token->prev;
	ft_lstdelone_token(token);
}
