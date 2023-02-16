/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:50:41 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/16 16:52:44 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "parsing.h"
#include "token_list_functions.h"
#include "libft.h"

static void		parse_token_list_for_wildcard(t_global *shell, \
				t_token **head_list, t_token *token, t_list *file_list);
static t_token	*parse_filelist_for_matching_filenames(t_global *shell, \
				char *pattern, t_list *file);
void			assign_ambiguous_redirect(t_global *shell, t_token *token, \
				t_token *expanded_wildcard);

void	expand_wildcard(t_global *shell, t_token **head_list)
{
	DIR				*directory;
	struct dirent	*dir;
	t_list			*file_list;
	t_list			*file;
	char			*filename;

	directory = opendir(".");
	file_list = NULL;
	if (directory)
	{
		dir = readdir(directory);
		while (dir != NULL)
		{
			filename = ft_strdup(dir->d_name);
			test_failed_malloc(shell, filename);
			file = ft_lstnew(filename);
			test_failed_malloc(shell, file);
			ft_lstadd_back(&file_list, file);
			dir = readdir(directory);
		}
		closedir(directory);
	}
	if (file_list)
		parse_token_list_for_wildcard(shell, head_list, *head_list, file_list);
	ft_lstclear(&file_list, free);
}

static void	parse_token_list_for_wildcard(t_global *shell, \
t_token **head_list, t_token *token, t_list *file_list)
{
	t_token	*expanded_token_list;
	t_token	*temp;

	while (token)
	{
		expanded_token_list = NULL;
		if ((token->token == CMD || token->token == DOLLAR) \
			&& ft_is_inside('*', token->str))
		{
			expanded_token_list = parse_filelist_for_matching_filenames(\
			shell, token->str, file_list);
			if (expanded_token_list)
			{
				assign_ambiguous_redirect(shell, token, expanded_token_list);
				insert_token_list(head_list, \
					token, expanded_token_list);
				temp = token;
				token = token->next;
				ft_lstdelone_token(temp);
			}
		}
		if (!expanded_token_list)
			token = token->next;
	}
}

static t_token	*parse_filelist_for_matching_filenames(t_global *shell, \
	char *pattern, t_list *file)
{
	t_token	*expanded_wildcard_list;
	t_token	*wildcard_token;
	char	*matched_file;
	char	*pattern_copy;

	expanded_wildcard_list = NULL;
	while (file)
	{
		pattern_copy = ft_strdup(pattern);
		test_failed_malloc(shell, pattern_copy);
		matched_file = find_matching_filenames(shell, pattern_copy, file);
		if (matched_file)
		{
			wildcard_token = ft_lstnew_token(matched_file, CMD);
			ft_lstadd_back_token(&expanded_wildcard_list, wildcard_token);
		}
		file = file->next;
		free(pattern_copy);
	}
	return (expanded_wildcard_list);
}

void	assign_ambiguous_redirect(t_global *shell, t_token *token, \
	t_token *expanded_wildcard)
{
	if (expanded_wildcard->next)
		expanded_wildcard->ambiguous_redirect = true;
	free(expanded_wildcard->origin_token_str);
	expanded_wildcard->origin_token_str = ft_strdup(token->origin_token_str);
	test_failed_malloc(shell, expanded_wildcard->origin_token_str);
}
