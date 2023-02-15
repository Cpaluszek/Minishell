/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_fd_to_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:15:18 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/02/15 20:57:16 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include "errors.h"
#include <unistd.h>
#include <stdio.h>

void	test_failed_malloc(t_global *shell, void *content);

void    add_fd_to_list(t_global *shell, int *fd)
{
    t_list  *new_fd;

    new_fd = ft_lstnew(fd);
    test_failed_malloc(shell, new_fd);
    ft_lstadd_back(&shell->block_fd_list, new_fd);
}

void	close_all_file_descriptors(t_list *fd_list)
{
	int	*fd;
	
	while (fd_list)
	{
		fd = (int *)fd_list->content;
		if (fd && *fd != -1)
			close(*fd);
		fd_list = fd_list->next;
	}
}
