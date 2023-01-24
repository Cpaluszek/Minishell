/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:45:52 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/24 10:09:09 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <unistd.h>

// Note: protect close ?
void	parent_close_pipes(t_token *token)
{
	if (token->make_a_pipe)
		close(token->pipe_fd[1]);
	if (token->prev && token->prev->make_a_pipe)
		close(token->prev->pipe_fd[0]);
}

int	args_number(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}
