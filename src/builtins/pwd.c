/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:45 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/18 17:00:20 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The pwd utility writes the absolute pathname of the current working directory
// to the standard output.
#include "structs.h"
#include <stdio.h>
#include <unistd.h>

int	ft_pwd(t_token *token, t_global *shell)
{
	(void) token;
	(void) shell;
	dprintf(STDERR_FILENO, "pwd execution\n");
	return (0);
}
