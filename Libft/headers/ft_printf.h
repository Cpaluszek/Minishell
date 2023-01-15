/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:32:57 by jlitaudo          #+#    #+#             */
/*   Updated: 2022/12/16 13:43:19 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

# define MIN_INT -2147483648

int		ft_printf(const char *text, ...);
int		ft_dprintf(int fd, const char *text, ...);
int		print_putchar(char c, int fd);
int		print_putstr(char *s, int fd);
int		print_putnbr(int n, int fd);
int		print_pointer(unsigned long long n, int fd);
int		print_putnbr_hex_low(unsigned int n, int fd);
int		print_putnbr_hex_cap(unsigned int n, int fd);
int		print_putnbr_unsigned(unsigned int n, int fd);

#endif