/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:47:45 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/09 15:18:17 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnbr_fd(int nb, int fd)
{
	unsigned int	num;
	char			c;

	if (nb < 0)
	{
		num = -nb;
		write(fd, "-", 1);
	}
	else
		num = nb;
	if (num > 9)
		ft_putnbr_fd(num / 10, fd);
	c = '0' + (num % 10);
	write(fd, &c, 1);
}
