/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:36 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/14 11:03:24 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Print a list of environement variables
#include "structs.h"
#include <stdio.h>
#include <unistd.h>

int	ft_env(t_token *token)
{
	(void) token;
	dprintf(STDERR_FILENO, "env execution\n");
	return (0);
}
