/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_matching_filenames.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:17:14 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/09 13:32:31 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"

static char	*process_filename_with_pattern(char *filename, char *pattern);
static int	parse_pattern_until_next_last_non_star_character(char **pattern);
void		test_failed_malloc(t_global *shell, void *content);

char	*find_matching_filenames(t_global *shell, char *pattern, t_list *file)
{
	char	*filename;
	int		i;

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

static char	*process_filename_with_pattern(char *filename, char *pattern)
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

static int	parse_pattern_until_next_last_non_star_character(char **pattern)
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
