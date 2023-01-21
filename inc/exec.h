/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:57:23 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/21 12:38:39 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

// Todo: move includes closer to usage
# include "structs.h"
# include <sys/wait.h>
# include <fcntl.h>

int		exec_start(t_global *shell);
void	setup_redirections(t_token *tok);
int		exec_token_list(t_token *token, t_global *shell);
int		exec_cmd(t_token *token, t_global *shell);
void	exec_child(t_token *token, char **env);

void	error_exit_exec(t_global *shell, char *err_msg);
void	exit_exec(t_global *shell, int exit_code);

/*	Builtins	*/
// Note: some builtins are found in PATH
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

/*	Utils	*/
void	update_env(t_global *shell);
int		args_number(char **args);
t_list	*search_in_env(t_list *env_list, char *identifier);
int		is_valid_identifier(char *str);
int		cmp_str(void *data1, void *data2);
void	*copy_content_str(void *entry);

#endif