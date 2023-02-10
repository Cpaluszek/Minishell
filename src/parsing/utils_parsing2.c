/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:49:00 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/02/10 11:21:59 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "exec.h"
#include "token_list_functions.h"

int	print_syntax_error(t_global *shell, char *str)
{
	ft_printf_fd(2, "%s: %s`%s'\n", MININAME, ERR_SYNTAX, str);
	shell->command_line = SYNTAX_ERROR;
	add_history(shell->input_completed);
	return (1);
}
