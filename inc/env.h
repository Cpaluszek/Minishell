/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 09:46:52 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/26 09:52:38 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

char	*expand_env_var(t_global *shell, char *identifier);
void	update_env(t_global *shell);
t_list	*search_in_env(t_list *env_list, char *identifier);
void	add_env_variable(t_global *shell, char *new_var);
int		is_valid_identifier(char *str);

#endif