/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:57:23 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/15 10:22:34 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "structs.h"
# include "errors.h"

# define COMMAND_NOT_FOUND 127

typedef struct s_exec {
	t_token	*cmd;
	t_token	*first_token;
	int		*pipe;
	int		flag;
}	t_exec;

// void	exec_start(t_global *shell, t_token *token_list);
int		exec_token_list(t_token *token, t_global *shell);
void	exec_block(t_global *shell, t_block *block);
int		exec_child(t_global *shell, t_token *token, t_token *command);
void	wait_for_token_list(t_token *token);
void	parent_close_pipes(t_token *token);
void	close_token_pipes(t_token *token);
int		*create_pipe(t_global *shell, t_exec *data, int p_end);

/*
	--------- Exec Errors -----------
*/
void	exec_cmd_error(t_global *shell, char *err, t_token *token);
int		exec_cmd_not_found(t_token *token);

/*
	--------- Redirections functions -----------
*/
void	open_and_immediatly_close_redirection(t_token *token);
void	set_redirection_for_token(t_block *block, t_token *token_list);
void	set_block_redirections(t_global *shell, t_block *block);
void	close_all_file_descriptors(t_list *fd_list);
void    add_fd_to_list(t_global *shell, int *fd);
int		open_block_redirections(t_block *block);
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
