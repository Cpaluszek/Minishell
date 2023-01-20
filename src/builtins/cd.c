/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:29 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/18 17:03:33 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// change current working directory
// only with relative or absolute path
#include "structs.h"
#include "exec.h"
#include <unistd.h>
#include <stdio.h>

// static int	cd_home(void);
// static int	cd_old(void);

// Todo: test with directory without permissions
int	ft_cd(t_token *token, t_global *shell)
{
	(void) token;
	(void) shell;
	dprintf(STDERR_FILENO, "cd execution\n");
	return (0);
	// char	*target;
	// int		err;

	// (void) err;
	// if (args_number(token->cmd) > 2)
	// 	return (1);
	// else if (args_number(token->cmd) == 1)
	// 	return (cd_home());
	// target = token->cmd[1];
	// if (target[0] == '-')
	// 	return (cd_old());
	// return (chdir(target));
}

// static int	cd_home(void)
// {
// 	// char	*home_path;

// 	// Todo: check in env for HOME
// 	return (0);
// }

// static int	cd_old(void)
// {
// 	// char	*previous_path;

// 	// Todo: search in env for OLDPWD
// 	return (0);
// }
