/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 12:00:42 by cpalusze          #+#    #+#             */
/*   Updated: 2022/11/27 12:06:18 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_lower_hex_fd(size_t nb, int fd)
{
	size_t	base_len;

	base_len = ft_strlen(HEX_BASE_LOWER);
	return (ft_print_size_t_base_fd(nb, HEX_BASE_LOWER, base_len, fd));
}

int	ft_print_upper_hex_fd(size_t nb, int fd)
{
	size_t	base_len;

	base_len = ft_strlen(HEX_BASE_UPPER);
	return (ft_print_size_t_base_fd(nb, HEX_BASE_UPPER, base_len, fd));
}
