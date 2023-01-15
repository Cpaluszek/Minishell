/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_putnbr_hex_cap.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:00:24 by jlitaudo          #+#    #+#             */
/*   Updated: 2022/12/16 13:35:12 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_putnbr_hex_cap(unsigned int n, int fd)
{
	int	len;

	if (n >= 16)
	{
		len = print_putnbr_hex_cap(n / 16, fd);
		print_putchar(BASE_HEX_CAP[n % 16], fd);
		return (1 + len);
	}
	print_putchar(BASE_HEX_CAP[n % 16], fd);
	return (1);
}
