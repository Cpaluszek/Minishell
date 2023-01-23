/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:25:43 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/23 13:51:32 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ERR_SYNTAX "syntax error near unexpected token "
# define ERR_DOLLAR "ambiguous redirect\n"
# define ERR_MALLOC "Error with malloc(3)\n"
# define ERR_FORK	"Error with fork()\n"
# define ERR_PIPE	"Error with pipe()\n"
# define ERR_DUP2	"Error with dup2()\n"
# define ERR_EXEC	"Error with execve()\n"

#endif