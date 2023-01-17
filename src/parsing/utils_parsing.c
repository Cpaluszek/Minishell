/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:49:00 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/01/17 19:00:05 by jlitaudo         ###   ########.fr       */
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
		if (!not_only_spaces(input) && ft_strlen(input))
			add_history(input);
		if (!(input == NULL || ft_strlen(input) == 0 || !not_only_spaces(input)))
			break ;
	}
	ft_free(shell->input);
	shell->input = input;
	shell->input_completed = ft_strjoin_and_free(shell->input_completed, input);
	if (!shell->input_completed)
		error_exit_parsing(shell, ERR_MALLOC);
}

int	not_only_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		if (line[i++] != ' ')
			return (i);
	if (line[i] == '\n')
		return (i);
	return (0);
}

void	error_exit_parsing(t_global *shell, char *err_msg)
{
	ft_printf_fd(2, "%s", err_msg);
	ft_free_split(shell->env);
	ft_free_split(shell->path);
	ft_lstclear_token(&shell->token_list);
	ft_lstclear(&shell->env_list, free);
	ft_free(shell->input);
	ft_free(shell->input_completed);
	exit(EXIT_FAILURE);
}
