/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:57:23 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/18 17:33:44 by cpalusze         ###   ########.fr       */
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
void	setup_redirections(t_token *tok);
int		exec_cmd(t_token *token, char **env);

/*	Builtins	*/
int		ft_echo(t_token *token);
int		ft_cd(t_token *token);
int		ft_pwd(t_token *token);
int		ft_export(t_token *token);
int		ft_unset(t_token *token);
int		ft_env(t_token *token);
int		ft_exit(t_token *token);
int		args_number(char **args);

#endif