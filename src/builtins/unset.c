/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:48 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/18 16:52:26 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Remove a variable from environment
// Can remove multiples variables at once
	// unset a b c
#include "structs.h"
#include <stdio.h>
#include <unistd.h>

int	ft_unset(t_token *token, t_global *shell)
{
	(void) token;
	(void) shell;
	dprintf(STDERR_FILENO, "unset execution\n");
	return (0);
}
