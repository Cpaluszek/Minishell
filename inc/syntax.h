/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 10:26:04 by Teiki             #+#    #+#             */
/*   Updated: 2023/02/06 10:40:21 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H

int	token_at_end_of_command_line(t_global *shell, t_token *token);
int	early_closing_parenthesis(t_global *shell, t_token *token);
int	cmd_before_or_after_parenthesis(t_global *shell, \
	t_token *token, enum e_token type);
int	print_syntax_error(t_global *shell, char *str);
int	two_tokens_in_a_row(t_global *shell, t_token *token1, t_token *token2);


#endif