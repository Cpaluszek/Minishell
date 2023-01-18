/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:08:04 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/17 11:09:17 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <unistd.h>

// Todo: rename file
// NOTE: search in PATH in parsing
/**
 * @brief Check for command access in absolute path, 
 * 
 * @param str input command
 * @return char** path to command and arguments splitted
 */
char	**find_exec(char *str)
{
	char	**cmd;

	cmd = ft_split(str, ' ');
	if (cmd == NULL)
		return (NULL);
	if (access(cmd[0], X_OK) == 0)
		return (cmd);
	return (cmd);
}
