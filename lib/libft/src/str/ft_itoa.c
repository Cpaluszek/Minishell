/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:29:57 by cpalusze          #+#    #+#             */
/*   Updated: 2022/11/12 10:04:44 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_digit_count(long int n);
static char	*ft_zero_toa(void);

char	*ft_itoa(int n)
{
	char		*str;
	long int	nb;
	int			i;

	if (n == 0)
		return (ft_zero_toa());
	i = ft_digit_count(n);
	nb = n;
	str = (char *) malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	str[i--] = 0;
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		str[i--] = nb % 10 + '0';
		nb /= 10;
	}
	return (str);
}

static char	*ft_zero_toa(void)
{
	char	*str;

	str = (char *) malloc(sizeof(char) * 2);
	if (str == NULL)
		return (NULL);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

static int	ft_digit_count(long int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}
