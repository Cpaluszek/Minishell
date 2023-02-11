/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:57:23 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/10 17:17:19 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "structs.h"
# include "errors.h"

# define COMMAND_NOT_FOUND 127
# define HERE_DOC_TMP	".heredoc.tmp"

typedef struct s_exec {
	t_token	*cmd;
	int		*pipe;
	int		redirs[2];
	int		flag;
}	t_exec;

int		exec_start(t_global *shell);
int		exec_child(t_token *token, char **env);
void	wait_for_token_list(t_token *token);
void	parent_close_pipes(t_token *token);
void	close_token_pipes(t_token *token);
int		*create_pipe(t_global *shell, t_exec *data, int p_end);

/*
	--------- Exec Errors -----------
*/
void	exec_cmd_error(t_global *shell, char *err, t_token *token);
void	exec_cmd_not_found(t_token *token);

/*
	--------- Redirections functions -----------
*/
void	close_redirs(int redirs[2]);
void	set_redirection(t_global *shell, t_token *tok, int redirs[2]);
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

#endif
