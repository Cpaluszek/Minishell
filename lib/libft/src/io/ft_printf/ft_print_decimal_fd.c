/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_decimal_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 11:59:28 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/09 15:19:05 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	ft_print_decimal_fd(const int nb, int fd)
{
	if (nb >= 0)
		return (ft_print_unsigned_int_fd(nb, fd));
	write(fd, "-", 1);
	return (1 + ft_print_unsigned_int_fd(-nb, fd));
}
