/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:39:04 by cpalusze          #+#    #+#             */
/*   Updated: 2022/11/26 11:57:22 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c);
static char		**ft_split_strings(char const *s, char c, size_t count);
static char		**ft_freeall(char **s);

char	**ft_split(char const *s, char c)
{
	size_t	strings_count;

	if (s == NULL)
		return (NULL);
	strings_count = ft_count_words(s, c);
	return (ft_split_strings(s, c, strings_count));
}

static size_t	ft_count_words(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	**ft_split_strings(char const *s, char c, size_t count)
{
	char	**split;
	size_t	i;
	size_t	j;
	size_t	len;

	split = (char **) ft_calloc(count + 1, sizeof(char *));
	if (split == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_strlen(s) && s[i] && j < count)
	{
		len = 0;
		if (s[i] != c)
		{
			while (s[i + len] && s[i + len] != c)
				len++;
			split[j++] = ft_substr(s, i, len);
			if (split[j - 1] == NULL)
				return (ft_freeall(split));
		}
		i += len + 1;
	}
	return (split);
}

static char	**ft_freeall(char **s)
{
	size_t	i;

	i = 0;
	while (s[i] != NULL)
	{
		free(s[i]);
		i++;
	}
	free (s);
	return (NULL);
}
