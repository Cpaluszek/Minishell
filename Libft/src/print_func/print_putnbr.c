/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_putnbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:10:35 by jlitaudo          #+#    #+#             */
/*   Updated: 2022/12/16 13:42:36 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_putnbr(int n, int fd)
{
	int	a;

	if (n == MIN_INT)
		return (print_putstr("-2147483648", fd));
	else if (n < 0)
	{
		print_putchar('-', fd);
		return (1 + print_putnbr(-n, fd));
	}
	if (n >= 10)
	{
		a = print_putnbr(n / 10, fd);
		print_putchar(n % 10 + '0', fd);
		return (1 + a);
	}
	print_putchar(n % 10 + '0', fd);
	return (1);
}
