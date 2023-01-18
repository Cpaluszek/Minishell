/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:48 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/18 16:33:38 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Remove a variable from environment
// Can remove multiples variables at once
	// unset a b c
#include "structs.h"

// Note: if unset with | execute with a child (copy of env)
// Export and unset works only without forks
int	ft_unset(t_token *token)
{
	(void) token;
	return (0);
}
