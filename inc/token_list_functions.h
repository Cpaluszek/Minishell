/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_functions.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:02:27 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/23 13:02:27 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_LIST_FUNCTIONS_H
# define TOKEN_LIST_FUNCTIONS_H

# include "structs.h"

/*
	--------- Chainlist tokens functions -----------
*/

void	ft_lstadd_back_token(t_token **lst, t_token *new);
void	ft_lstdelone_token(t_token *lst);
void	ft_lstclear_token(t_token **lst);
t_token	*ft_lstlast_token(t_token *lst);
t_token	*ft_lstnew_token(char	*content, enum e_token token);

/*
	--------- Chainlist blocks functions -----------
*/

t_block	*ft_lstnew_block(t_block *upper_block, t_token *token_list);
void	ft_lstadd_back_block(t_block **lst, t_block *new);
void	ft_lstdelone_block(t_block *lst);
void	ft_lstclear_block(t_block **lst);

#endif