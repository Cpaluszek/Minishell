/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 09:46:52 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/27 13:51:03 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

void	update_env(t_global *shell);
t_list	*search_in_env(t_list *env_list, char *identifier);
void	add_env_variable(t_global *shell, char *new_var);
int		is_valid_identifier(char *str);

/*	Expand variable	*/
char	*check_for_expand(t_global *shell, char *buff);

#endif