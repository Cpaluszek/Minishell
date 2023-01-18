/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:29 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/18 16:30:18 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "exec.h"
#include <unistd.h>

static int	cd_home(void);
static int	cd_old(void);

// Note: what is errno = EFAULT
// Todo: cd - -> OLDPWD
int	ft_cd(t_token *token)
{
	char	*target;
	int		err;

	(void) err;
	if (args_number(token->cmd) > 2)
		return (1);
	else if (args_number(token->cmd) == 1)
		return (cd_home());
	target = token->cmd[1];
	if (target[0] == '-')
		return (cd_old());
	return (chdir(target));
}

static int	cd_home(void)
{
	// char	*home_path;

	// Todo: check in env for HOME
	return (0);
}

static int	cd_old(void)
{
	// char	*previous_path;

	// Todo: search in env for OLDPWD
	return (0);
}
