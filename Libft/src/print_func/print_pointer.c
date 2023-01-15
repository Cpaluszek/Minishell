/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:00:24 by jlitaudo          #+#    #+#             */
/*   Updated: 2022/12/16 13:34:51 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_pointer(unsigned long long n, int fd)
{
	int	a;

	if (n >= 16)
	{
		a = print_pointer((n / 16), fd);
		print_putchar(BASE_HEX_LOW[n % 16], fd);
		return (1 + a);
	}
	print_putchar(BASE_HEX_LOW[n % 16], fd);
	return (1);
}
