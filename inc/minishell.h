/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:07:09 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/25 11:11:47 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "structs.h"

# define STDIN	0
# define STDOUT	1
# define STDERR	2

void	free_structs(t_global *shell);
void	error_exit_shell(t_global *shell, char *err_msg);
void	exit_shell(t_global *shell, int exit_code);
void	exit_shell_from_signal(t_global *shell);

#endif