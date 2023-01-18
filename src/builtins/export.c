/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:42 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/18 16:33:10 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Add variable to environment
// Multiple variables can be exported
	// export a="1" b="2" c="3"
#include "structs.h"

// Export without parameters will print sorted env (ASCII order)

// Note: if export with | execute with a child (copy of env)
int	ft_export(t_token *token)
{
	(void) token;
	return (0);
}
