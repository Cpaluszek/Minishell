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
#include "exec.h"
#include <stdio.h>
#include <unistd.h>

int	ft_env(t_token *token, t_global *shell)
{
	int	i;

	(void) token;
	if (args_number(token->cmd) > 1)
		return (1);
	i = 0;
	while (shell->env[i])
	{
		printf("%s\n", shell->env[i]);
		i++;
	}
	return (0);
}
