/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:57:23 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/08 16:59:34 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

// Todo: move includes closer to usage
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "structs.h"
# include "errors.h"

# define COMMAND_NOT_FOUND 127
# define HERE_DOC_TMP	"/tmp/.heredoc.tmp"

int		exec_start(t_global *shell);
int		exec_child(t_token *token, char **env);
void	parent_close_pipes(t_token *token);
void	close_token_pipes(t_token *token);

/*
	--------- Redirections functions -----------
*/
int		setup_all_redirections(t_global *shell, t_token *tok);
void	close_all_redirections(t_token *tok);
void	close_redirections(t_token *tok);
int		setup_input_redir(t_token *tok, t_global *shell, int fd_redir_in);
int		setup_output_redir(t_token *tok, int fd_redir_out);
int		dup_fds(t_token *token);

/*
	--------- Builtins functions -----------
*/
typedef struct s_builtin {
	char	*name;
	int		(*builtin)(t_token *, t_global *);
}	t_builtin;

int		check_for_builtins(t_token *token, t_global *shell);
int		ft_echo(t_token *token, t_global *shell);
int		ft_cd(t_token *token, t_global *shell);
int		ft_pwd(t_token *token, t_global *shell);
int		ft_export(t_token *token, t_global *shell);
int		ft_unset(t_token *token, t_global *shell);
int		ft_env(t_token *token, t_global *shell);
int		ft_exit(t_token *token, t_global *shell);

int		any_pipe_in_token_list(t_token *token);

/*
	--------- Utils functions -----------
*/
char	*ft_getcwd(void);
int		args_number(char **args);
int		cmp_str(void *data1, void *data2);
void	*copy_content_str(void *entry);
void	exec_cmd_error(t_global *shell, char *err, t_token *token);

#endif
