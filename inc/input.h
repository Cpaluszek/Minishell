/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 12:31:35 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/12 15:51:55 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "structs.h"

int		here_doc(t_global *shell, t_token *token);

/*
	--------- Signals functions -----------
*/
void	init_shell_attr(t_global *shell);
void	set_interactive_signals(t_global *shell);
void	set_execution_signals(t_global *shell);
void	set_here_doc_signals(t_global *shell);

/*
	--------- Signals Handlers -----------
*/
void	handle_interactive_sigquit(int signum, siginfo_t *info, void *context);
void	handle_abort_input(int signum, siginfo_t *info, void *context);
void	handle_execution_sigint(int signum, siginfo_t *info, void *context);
void	handle_execution_sigquit(int signum, siginfo_t *info, void *context);
void	handle_here_doc_sigint(int signum, siginfo_t *info, void *context);

#endif