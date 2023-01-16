/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:49:00 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/01/16 19:26:02 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "token_list_functions.h"

void	get_input(t_global *shell, char *prompt)
{
	char	*input;

	input = NULL;
	while (1)
	{
		ft_free(input);
		input = readline(prompt);
		if (!(input == NULL || ft_strlen(input) == 0 || only_spaces(input)))
			break ;
	}
	shell->input = ft_strjoin_and_free(shell->input, input);
	ft_free(input);
	if (!shell->input)
		error_exit_parsing(shell);
}

int	only_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		if (line[i++] != ' ')
			return (0);
	if (line[i] == '\n')
		return (1);
	return (1);
}

void	error_exit_parsing(t_global *shell, char *err_msg)
{
	ft_printf_fd(2, "%s", err_msg);
	ft_lstclear_token(shell->token_list);
	ft_free(shell->input);
	exit(EXIT_FAILURE);
}
