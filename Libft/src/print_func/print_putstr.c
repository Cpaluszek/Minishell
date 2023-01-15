/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_putstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:03:47 by jlitaudo          #+#    #+#             */
/*   Updated: 2022/12/16 13:37:05 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_putstr(char *s, int fd)
{
	int	len;

	if (!s)
	{
		write (fd, "(null)", 6);
		return (6);
	}
	len = ft_strlen(s);
	write(fd, s, len);
	return (len);
}
