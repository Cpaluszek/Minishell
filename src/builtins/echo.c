/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:33 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/17 16:25:49 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Writes argument to STDOUT
// Option -n: print without trailing newline
// The echo utility exits 0 on success, and >0 if an error occurs.
#include "structs.h"
#define OPTION "\n"

int	ft_echo(t_token *token)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	// Skip all "-n" and "-nnnnn"
	while (ft_strncmp("-n", OPTION, ft_strlen(OPTION)))
	{
		new_line = 0;
		i++;
	}		
}