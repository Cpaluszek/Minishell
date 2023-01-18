/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:33 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/18 17:04:22 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Writes argument to STDOUT
// Option -n: print without trailing newline
// The echo utility exits 0 on success, and >0 if an error occurs.
#include "structs.h"
#include <unistd.h>
#define OPTION "-n"

static int	echo_option(t_token *token, int *i);

int	ft_echo(t_token *token)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = echo_option(token, &i);
	while (token->cmd[i])
	{
		ft_putstr_fd(token->cmd[i], STDOUT_FILENO);
		if (token->cmd[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (new_line)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

// Skip all "-n" and "-nnnnn"
static int	echo_option(t_token *token, int *i)
{
	int	new_line;
	int	j;

	new_line = 1;
	j = 0;
	while (ft_strncmp(token->cmd[*i], OPTION, ft_strlen(OPTION)) == 0)
	{
		j += ft_strlen(OPTION);
		while (token->cmd[*i][j])
		{
			if (token->cmd[*i][j] != 'n')
			{
				if (*i == 1)
					return (1);
				else
					return (new_line);
			}	
		}
		(*i)++;
	}
	return (new_line);
}