/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:39:24 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/13 12:40:27 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 2048
#endif

static char	*read_file(int fd, char *buffer, size_t i);
static char	*ft_join_to_buffer(char *buffer, char *read);
static char	*ft_get_line(char *buffer);
static char	*ft_remove_current_line(char *buffer);

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_file(fd, buffer, 0);
	if (buffer == NULL)
		return (NULL);
	line = ft_get_line(buffer);
	buffer = ft_remove_current_line(buffer);
	return (line);
}

static char	*read_file(int fd, char *buffer, size_t i)
{
	char	*content;
	ssize_t	byte_count;

	content = (char *) malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (content == NULL)
		return (NULL);
	byte_count = 1;
	while (byte_count > 0)
	{
		byte_count = read(fd, content, BUFFER_SIZE);
		if (byte_count == -1)
		{
			free(content);
			free(buffer);
			return (NULL);
		}
		content[byte_count] = '\0';
		buffer = ft_join_to_buffer(buffer, content);
		i = 0;
		while (buffer[i] && buffer[i] != '\n')
			i++;
		if (buffer[i] && buffer[i] == '\n')
			break ;
	}
	return (free(content), buffer);
}

static char	*ft_join_to_buffer(char *buffer, char *read)
{
	char	*join;

	join = ft_strjoin(buffer, read);
	free(buffer);
	return (join);
}

static char	*ft_get_line(char *buffer)
{
	char	*line;
	size_t	i;

	i = 0;
	if (buffer[i] == '\0')
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_substr(buffer, 0, i + 1);
	if (line == NULL)
		return (NULL);
	return (line);
}

static char	*ft_remove_current_line(char *buffer)
{
	size_t	i;
	char	*remaining;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	remaining = ft_substr(buffer, i + 1, ft_strlen(buffer) - i);
	if (remaining == NULL)
		return (NULL);
	free(buffer);
	return (remaining);
}
