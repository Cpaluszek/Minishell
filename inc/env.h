/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 09:46:52 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/30 15:18:33 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "libft.h"
# include "structs.h"

# define VAR_LIMITER "$ \n\"\'|*=-+/%.,!@#^&[]{}_:;<>"
# define CONCAT_VAR "+="

void	update_env(t_global *shell);
t_list	*search_in_env(t_list *env_list, char *identifier);
void	add_env_variable(t_global *shell, char *new_var);
void	concat_env_variable(t_global *shell, char *new_var, t_list *search);
int		is_valid_identifier(char *str);

/*	Setup env	*/
char	**set_minimum_env(void);
void	**increment_shlvl(t_global *sh);

/*	Expand variable	*/
char	*check_for_expand(t_global *shell, char *buff);

#endif