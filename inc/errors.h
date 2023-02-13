/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:25:43 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/29 12:45:50 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ERR_SYNTAX 		"syntax error near unexpected token "

// Note: ERR_DOLLAR is never used
# define ERR_DOLLAR 		"ambiguous redirect\n"
# define ERR_MALLOC 		"Error with malloc(3)\n"
# define ERR_FORK			"fork"
# define ERR_PIPE			"pipe"
# define ERR_DUP2			"dup2"
# define ERR_EXEC			"execve"
# define ERR_WRITE			"write"
# define ERR_CLOSE			"close"
# define ERR_TCSET			"tcsetattr"
# define ERR_TCGET			"tcgetattr"

#endif