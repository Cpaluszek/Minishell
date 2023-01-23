/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:57:23 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/23 14:55:20 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

// Todo: move includes closer to usage
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "structs.h"
# include "errors.h"

# define STDIN	0
# define STDOUT	1
# define STDERR	2

# define COMMAND_NOT_FOUND 127

int		exec_start(t_global *shell);
void	setup_all_redirections(t_token *tok);
void	close_all_redirections(t_token *tok);
void	close_redirections(t_token *tok);
int		exec_token_list(t_token *token, t_global *shell);
void	exec_cmd(t_token *token, t_global *shell);
int		exec_child(t_token *token, char **env);

/*
	--------- Signals functions -----------
*/
void	init_shell_attr(t_global *shell);
void	set_interactive_signals(t_global *shell);
void	set_execution_signals(void);
void	handle_interactive_sigquit(int signum, siginfo_t *info, void *context);
void	handle_abort_input(int signum, siginfo_t *info, void *context);
void	handle_execution_sigint(int signum, siginfo_t *info, void *context);
void	handle_execution_sigquit(int signum, siginfo_t *info, void *context);

/*
	--------- Builtins functions -----------
*/
typedef struct s_builtin {
	char	*name;
	int		(*builtin)(t_token *, t_global *);
}	t_builtin;

int		parse_builtins(t_token *token, int*is_builtin, t_global *shell);
int		ft_echo(t_token *token, t_global *shell);
int		ft_cd(t_token *token, t_global *shell);
int		ft_pwd(t_token *token, t_global *shell);
int		ft_export(t_token *token, t_global *shell);
int		ft_unset(t_token *token, t_global *shell);
int		ft_env(t_token *token, t_global *shell);
int		ft_exit(t_token *token, t_global *shell);

/*
	--------- Utils functions -----------
*/
char	*ft_getcwd(void);
void	update_env(t_global *shell);
int		args_number(char **args);
t_list	*search_in_env(t_list *env_list, char *identifier);
int		is_valid_identifier(char *str);
int		cmp_str(void *data1, void *data2);
void	*copy_content_str(void *entry);

#endif