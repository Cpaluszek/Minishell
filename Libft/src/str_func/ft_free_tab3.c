/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 10:29:01 by Teiki             #+#    #+#             */
/*   Updated: 2023/01/09 15:58:47 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	***ft_free_tab3(char ***tab)
{
	int	i;

	if (!tab)
		return (NULL);
	i = 0;
	while (tab[i])
		ft_free_tab(tab[i++]);
	free(tab);
	return (NULL);
}
