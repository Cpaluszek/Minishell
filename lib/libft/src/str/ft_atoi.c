/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:49:25 by cpalusze          #+#    #+#             */
/*   Updated: 2022/11/30 08:40:07 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int				i;
	int				sign;
	long long int	res;

	i = 0;
	sign = 1;
	while (nptr[i] && ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	res = 0;
	while (ft_isdigit(nptr[i]))
		res = res * 10 + (nptr[i++] - '0');
	return (res * sign);
}
