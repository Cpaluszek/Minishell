/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:25:43 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/24 11:31:32 by cpalusze         ###   ########.fr       */
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
# define ERR_WRITE	"Error with write()"
# define ERR_CLOSE	"Error with close()"
# define ERR_UNLINK	"Error with unlink()"
# define ERR_HERE_DOC_FILE	"Error with here_doc file"

#endif