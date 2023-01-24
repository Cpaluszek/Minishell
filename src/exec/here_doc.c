/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:06:39 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/24 14:09:23 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

#define HERE_DOC_PROMPT	"> "

static void	get_here_doc_input(t_global *shell, char *delim, int file);

// Note: how to manage here_doc file error ?
// Todo: multiple here_docs
// Todo: multiple here_docs will not work
// Note: not expand dollars in delimiter
// Todo: reset signals for here_doc + setattr
// Todo: manage suppr key in here_doc
void	here_doc(t_global *shell, t_token *token)
{
	int		file;
	char	*delimiter;

	file = open(HERE_DOC_TMP, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (file == -1)
		perror(ERR_HERE_DOC_FILE);
	delimiter = ft_strjoin(token->str, "\n");
	if (delimiter == NULL)
		error_exit_shell(shell, ERR_MALLOC);
	get_here_doc_input(shell, delimiter, file);
	free(delimiter);
	if (close(file) == -1)
		perror(ERR_CLOSE);
}

// Todo: expand $ after input
static void	get_here_doc_input(t_global *shell, char *delim, int file)
{
	char	*buff;

	while (1)
	{
		if (write(STDOUT, HERE_DOC_PROMPT, ft_strlen(HERE_DOC_PROMPT)) == -1)
		{
			free(delim);
			if (close(file) == -1)
				perror(ERR_CLOSE);
			error_exit_shell(shell, ERR_WRITE);
		}
		buff = get_next_line(STDIN);
		if (buff == NULL || ft_strnstr(buff, delim, ft_strlen(buff)) == buff)
			break ;
		// Todo: expand $var just before write
		if (write(file, buff, ft_strlen(buff)) == -1)
		{
			free(buff);
			free(delim);
			if (close(file) == -1)
				perror(ERR_CLOSE);
			error_exit_shell(shell, ERR_WRITE);
		}
		free(buff);
	}
	free(buff);
}
