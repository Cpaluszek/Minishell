/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:06:39 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/25 13:57:47 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

#define HERE_DOC_PROMPT	"> "

static void	get_here_doc_input(t_global *shell, char *delim, int file);
static void	here_doc_write_error(t_global *shell, char *delim, int file);
static char	*check_for_expand(t_global *shell, char *buff);

// Note: how to manage here_doc file error ?
// Todo: multiple here_docs will not work
// Note: not expand dollars in delimiter
// Todo: reset signals for here_doc + setattr
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
			here_doc_write_error(shell, delim, file);
		buff = get_next_line(STDIN);
		if (buff == NULL || ft_strnstr(buff, delim, ft_strlen(buff)) == buff)
			break ;
		// Todo: expand $var just before write
		buff = check_for_expand(shell, buff);
		if (write(file, buff, ft_strlen(buff)) == -1)
		{
			free(buff);
			here_doc_write_error(shell, delim, file);
		}
		free(buff);
	}
	free(buff);
}

static void	here_doc_write_error(t_global *shell, char *delim, int file)
{
	free(delim);
	if (close(file) == -1)
		perror(ERR_CLOSE);
	error_exit_shell(shell, ERR_WRITE);
}

static char	*check_for_expand(t_global *shell, char *buff)
{
	char	**split_buff;
	char	*dollar_pos;
	int		i;

	split_buff = ft_split(buff, ' ');
	if (split_buff == NULL)
	{
		free(buff);
		error_exit_shell(shell, ERR_MALLOC);
	}
	i = 0;
	while (split_buff[i])
	{
		dollar_pos = ft_strchr(split_buff[i], '$');
		if (dollar_pos != NULL)
		{
			split_buff[i] = expand_env_var(shell, split_buff[i] + 1);
		}
		i++;
	}
	i = 0;
	while (split_buff[i])
	{
		buff = ft_strjoin_and_free(buff, split_buff[i++]);
		if (buff == NULL)
		{
			ft_free_split(split_buff);
			error_exit_shell(shell, ERR_MALLOC);
		}
	}
	ft_free_split(split_buff);
	return (buff);
}
