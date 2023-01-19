/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:45:52 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/19 11:53:29 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "token_list_functions.h"

// Note: merge with error_exit_parsing ?
// Todo: add exit code parameter
void	error_exit_exec(t_global *shell, char *err_msg)
{
	ft_printf_fd(2, "%s", err_msg);
	ft_free_split(shell->env);
	ft_free_split(shell->path);
	ft_lstclear_token(&shell->token_list);
	ft_lstclear(&shell->env_list, free);
	ft_free(shell->input);
	ft_free(shell->input_completed);
	exit(EXIT_FAILURE);
}