/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:07:01 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/23 13:07:01 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	print_syntax_error(t_global *shell, char *str)
{
	ft_printf_fd(2, "%s: %s`%s'\n", MININAME, ERR_SYNTAX, str);
	shell->command_line = SYNTAX_ERROR;
	add_history(shell->input_completed);
	return (1);
}
