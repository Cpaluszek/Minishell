/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:57:23 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/14 11:06:01 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "structs.h"

/*	Builtins	*/

int	ft_echo(t_token *token);
int	ft_cd(t_token *token);
int	ft_pwd(s_token *token);
int	ft_export(t_token *token);
int	ft_unset(t_token *token);
int	ft_env(t_token *token);
int	ft_exit(s_token *token);



#endif