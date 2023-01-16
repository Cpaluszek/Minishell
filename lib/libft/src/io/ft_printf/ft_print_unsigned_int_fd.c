/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned_int_fd.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 08:16:15 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/09 15:19:16 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	ft_print_unsigned_int_fd(unsigned int nb, int fd)
{
	char	c;
	int		len;

	len = 1;
	if (nb > 9)
		len += ft_print_unsigned_int_fd(nb / 10, fd);
	c = '0' + (nb % 10);
	write(fd, &c, 1);
	return (len);
}
