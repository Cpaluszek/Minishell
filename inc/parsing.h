/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:57:49 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/15 22:57:40 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "structs.h"

# define ERR_SYNTAX "syntax error near unexpected token "

int		new_token(t_token **list, char *str, int len, enum e_token type);
t_token *quote_parsing(char *str);
t_token	*token_parsing(t_token *token_list);
t_token	*central_parsing(char *str);

#endif