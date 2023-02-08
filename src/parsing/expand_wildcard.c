/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:50:41 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/08 00:31:45 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "parsing.h"
#include "token_list_functions.h"
#include "libft.h"

void	expand_wildcard(t_global *shell)
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
			filename = strdup(dir->d_name);
			test_failed_malloc(shell, filename);
			file = ft_lstnew(filename);
			test_failed_malloc(shell, file);
			ft_lstadd_back(&file_list, file);
			dir = readdir(directory);
		}
		closedir(directory);
	}
	if (file_list)
		parse_token_list_for_wildcard(shell, shell->token_list, file_list);
	ft_lstclear(file_list, free);
}

static void	parse_token_list_for_wildcard(t_global *shell, \
t_token *token, t_list *file_list)
{
	t_token	*expanded_token_list;
	t_token	*temp;

	while (token)
	{
		if (token->token == CMD && ft_is_inside('*', token->str))
		{
			expanded_token_list = parse_filelist_for_matching_filenames(\
			shell, token->str, file_list);
			if (expanded_token_list)
			{
				insert_token_list(shell, token, expanded_token_list);
				temp = token;
				token = token->next;
				ft_lstdelone_token(temp);
			}
		}
		token = token->next;
	}
}

t_token	*parse_filelist_for_matching_filenames(t_global *shell, \
	char *pattern, t_list *file)
{
	t_token	*expanded_wildcard_list;
	t_token	*wildcard_token;
	char	*matched_file;

	expanded_wildcard_list = NULL;
	while (file)
	{
		matched_file = find_matching_filenames(shell, pattern, file);
		if (matched_file)
		{
			wildcard_token = ft_lstnew_token(matched_file, CMD);
			ft_lstadd_back_token(&expanded_wildcard_list, wildcard_token);
		}
		file = file->next;
	}
	return (expanded_wildcard_list);

}

char	*find_matching_filenames(t_global *shell, char *pattern, t_list *file)
{
	char	*filename;
	int		i;
	int		len;

	filename = (char *)file->content;
	i = 0;
	while (pattern[i] != '*')
		i++;
	if (ft_strncmp(filename, pattern, i))
		return (NULL);
	pattern = &pattern[i];
	filename = &filename[i];
	filename = process_filename_with_pattern(filename, pattern);
	if (!filename)
		return (NULL);
	filename = ft_strdup((char *)file->content);
	test_failed_malloc(shell, filename);
	return (filename);
}

char	*process_filename_with_pattern(char *filename, char *pattern)
{
	int	i;
	int	len;

	while (*pattern)
	{
		i = parse_pattern_until_next_last_non_star_character(&pattern);
		if (i == 0)
			break ;
		if (pattern[i] == 0)
		{
			len = ft_strlen(filename);
			if (len < i || ft_strncmp(&filename[len - i], pattern, i))
				return (NULL);
			break ;
		}
		pattern[i] = 0;
		filename = ft_strnstr(filename, pattern, ft_strlen(filename));
		if (!filename)
			return (NULL);
		pattern[i] = '*';
		pattern = &pattern[i];
		filename = &filename[i];
	}
	return (filename);
}

int	parse_pattern_until_next_last_non_star_character(char **pattern)
{
	int		i;
	char	*new_pattern;

	new_pattern = *pattern;
	i = 0;
	while (new_pattern[i] && new_pattern[i] == '*')
		i++;
	new_pattern = &new_pattern[i];
	*pattern = new_pattern;
	i = 0;
	while (new_pattern[i] && new_pattern[i] != '*')
		i++;
	return (i);
}
