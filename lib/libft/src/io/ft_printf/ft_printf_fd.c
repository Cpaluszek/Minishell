/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 12:23:03 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/09 15:19:27 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	ft_printf_fd(int fd, const char *input, ...)
{
	int		i;
	int		char_count;
	va_list	args;

	va_start(args, input);
	i = 0;
	char_count = ft_strlen(input);
	if (write(fd, 0, 0) == -1)
		return (-1);
	while (input[i])
	{
		if (input[i] == '%')
			char_count += ft_pick_conversion_fd(fd, input[++i], args) - 2;
		else
			ft_putchar_fd(input[i], fd);
		if (input[i])
			i++;
	}
	va_end(args);
	return (char_count);
}
