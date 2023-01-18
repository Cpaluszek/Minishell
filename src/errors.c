/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:07:38 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/18 16:52:03 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

// Print error message from errno and exit program
void	print_perror_exit(char *str)
{
	perror(str);
	exit(1);
}

// Print error message from errno
void	print_perror(char *str)
{
	perror(str);
}
