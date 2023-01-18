/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:57:23 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/18 16:49:42 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "structs.h"
# include <sys/wait.h>
# include <fcntl.h>


typedef struct s_builtin {
	char	*name;
	char	*usage;
	int		(*builtin)(t_token *);
}	t_builtin;

int		exec_start(t_global *shell);
int		exec_cmd(t_token *token, int *pipes_fd, int *pipe_index);
int		exec_token_list(t_block *block);
void	manage_redir_pipes(t_token *token, int *pipes_fd, int *pipe_index);
void	check_redir(t_token *token, int *input_fd, int *output_fd);
char	**find_exec(char *str);

/*	Builtins	*/

int	ft_echo(t_token *token);
int	ft_cd(t_token *token);
int	ft_pwd(s_token *token);
int	ft_export(t_token *token);
int	ft_unset(t_token *token);
int	ft_env(t_token *token);
int	ft_exit(s_token *token);



#endif