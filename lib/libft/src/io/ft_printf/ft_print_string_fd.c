/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:29:07 by cpalusze          #+#    #+#             */
/*   Updated: 2022/11/27 12:03:06 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_string_fd(const char *str, int fd)
{
	if (str == NULL)
	{
		ft_putstr_fd(NULL_STR, fd);
		return ((int)ft_strlen(NULL_STR));
	}
	ft_putstr_fd(str, fd);
	return ((int)ft_strlen(str));
}
