/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_putnbr_hex_low.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:00:24 by jlitaudo          #+#    #+#             */
/*   Updated: 2022/12/16 13:35:34 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_putnbr_hex_low(unsigned int n, int fd)
{
	int	a;

	if (n >= 16)
	{
		a = print_putnbr_hex_low(n / 16, fd);
		print_putchar(BASE_HEX_LOW[n % 16], fd);
		return (1 + a);
	}
	print_putchar(BASE_HEX_LOW[n % 16], fd);
	return (1);
}
