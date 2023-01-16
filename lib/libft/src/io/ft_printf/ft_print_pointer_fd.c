/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 12:00:59 by cpalusze          #+#    #+#             */
/*   Updated: 2022/11/27 12:16:01 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_pointer_fd(size_t ptr, int fd)
{
	size_t	b_len;

	b_len = ft_strlen(HEX_BASE_LOWER);
	ft_putstr_fd("0x", fd);
	return (2 + ft_print_size_t_base_fd(ptr, HEX_BASE_LOWER, b_len, fd));
}
