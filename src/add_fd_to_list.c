/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_fd_to_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:15:18 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/02/18 19:18:04 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include <unistd.h>

void	test_failed_malloc(t_global *shell, void *content);

void	add_fd_to_list(t_global *shell, int *fd)
{
	t_list	*new_fd;

	new_fd = ft_lstnew(fd);
	test_failed_malloc(shell, new_fd);
	ft_lstadd_back(&shell->block_fd_list, new_fd);
}

void	close_heredocs_file_descriptors(t_list *fd_list)
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
