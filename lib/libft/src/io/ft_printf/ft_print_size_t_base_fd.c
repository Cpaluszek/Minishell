/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_size_t_base_fd.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 12:02:33 by cpalusze          #+#    #+#             */
/*   Updated: 2022/11/27 12:02:35 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_size_t_base_fd(size_t nb, char *base, size_t b_len, int fd)
{
	int	char_count;

	char_count = 1;
	if (nb >= b_len)
		char_count += ft_print_size_t_base_fd(nb / b_len, base, b_len, fd);
	ft_putchar_fd(base[nb % b_len], fd);
	return (char_count);
}
