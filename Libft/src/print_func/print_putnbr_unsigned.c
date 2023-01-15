/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_putnbr_unsigned.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:10:35 by jlitaudo          #+#    #+#             */
/*   Updated: 2022/12/16 13:35:53 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_putnbr_unsigned(unsigned int n, int fd)
{
	int	a;

	if (n >= 10)
	{
		a = print_putnbr_unsigned(n / 10, fd);
		print_putchar(n % 10 + '0', fd);
		return (1 + a);
	}
	print_putchar(n % 10 + '0', fd);
	return (1);
}
