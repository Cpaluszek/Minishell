/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pick_conversion_fd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 11:58:29 by cpalusze          #+#    #+#             */
/*   Updated: 2022/11/27 12:15:27 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pick_conversion_fd(int fd, const char c, va_list args)
{
	if (c == 'd' || c == 'i')
		return (ft_print_decimal_fd(va_arg(args, int), fd));
	if (c == 's')
		return (ft_print_string_fd(va_arg(args, char *), fd));
	if (c == 'p')
		return (ft_print_pointer_fd(va_arg(args, size_t), fd));
	if (c == 'u')
		return (ft_print_unsigned_int_fd(va_arg(args, unsigned int), fd));
	if (c == 'x')
		return (ft_print_lower_hex_fd(va_arg(args, unsigned int), fd));
	if (c == 'X')
		return (ft_print_upper_hex_fd(va_arg(args, unsigned int), fd));
	if (c == 'c')
		ft_putchar_fd(va_arg(args, int), fd);
	else if (c == '%')
		ft_putchar_fd('%', fd);
	return (1);
}
