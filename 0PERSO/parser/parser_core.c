/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 10:56:31 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/07/05 10:52:20 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_token_syntax(char **array)
{
	int	i;

	i = 0;
	if (array[0][0] == '|')
		return (printf("bash: syntax error near unexpected token `|'\n"), -1);
	while (array[i] && array[i + 1])
	{
		if (array[i][0] == '|' || array[i][0] == '>' || array[i][0] == '<')
		{
			if (array[i + 1][0] == '>' && array[i + 1][1] == '>')
				return (printf("bash: syntax error near unexpected token `>>'\n"), -1);
			else if (array[i + 1][0] == '>')
				return (printf("bash: syntax error near unexpected token `>'\n"), -1);
			else if (array[i + 1][0] == '<' && array[i + 1][1] == '<')
				return (printf("bash: syntax error near unexpected token `<<'\n"), -1);
			else if (array[i + 1][0] == '<')
				return (printf("bash: syntax error near unexpected token `<'\n"), -1);
			else if (array[i + 1][0] == '|')
				return (printf("bash: syntax error near unexpected token `|'\n"), -1);
		}
		i++;
	}
	if (array[i][0] == '>' || array[i][0] == '<')
		return (printf("bash: syntax error near unexpected token `newline'\n"), -1);
	if (array[i][0] == '|' && i == 1)
		return (printf("bash: syntax error near unexpected token `|'\n"), -1);
	return (0);
}

void	build_tokens_list(char **array, int *list_words)
{
	int	i;
	int	last_token_position;
	int	i_recall;

	i = 0;
	while (array[i])
	{
		if (array[i][0] == '|' && array[i][1] == '\0')
			list_words[i] = PIPE;
		else if (array[i][0] == '>' && array[i][1] == '\0')
			list_words[i] = REDIR_OUT;
		else if (array[i][0] == '<' && array[i][1] == '\0')
			list_words[i] = REDIR_IN;
		else if (array[i][0] == '>' && array[i][1] == '>' && array[i][2] == '\0')
			list_words[i] = APPEND_REDIR_OUT;
		else if (array[i][0] == '<' && array[i][1] == '<' && array[i][2] == '\0')
			list_words[i] = HERE_DOC;
		else
			list_words[i] = UNKNOWN;
		i++;
	}
	last_token_position = -1;
	i_recall = 0;
	i = 0;
	while (list_words[i])
	{
		if (list_words[i] != PIPE && list_words[i] != REDIR_OUT && list_words[i] != REDIR_IN && list_words[i] != APPEND_REDIR_OUT)
		{
			list_words[i] = FILE_OR_COMMAND;
			i++;
		}
		while (list_words[i] && list_words[i] != PIPE && list_words[i] != REDIR_OUT && list_words[i] != REDIR_IN && list_words[i] != APPEND_REDIR_OUT)
		{
			list_words[i] = ARG_OR_OPTION;
			i++;
		}
		if (list_words[i])
			i++;
	}
	return ;
}

void	parsing_trimmer(char **array)
{
	int	i;
	int	j;

	i = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
		{
			if (array[i][j] == '\'' || array[i][j] == '\"')
			{
				while (array[i][j + 1])
				{
					array[i][j] = array[i][j + 1];
					j++;
				}
				array[i][j] = '\0';
				j = 0;
			}
			else
			{
				j++;
			}
		}
		i++;
	}
	array = NULL;
	return ;
}

int	check_file_syntax(char **array, int *list_words)
{
	char	*path_env;
	char	**path_array;
	int		i;

	path_env = getenv("PATH");
	path_array = mini_split(path_env, ':');
	i = 0;
	while (path_array[i])
	{
		printf("PATH[%d] %s\n", i, path_array[i]);
		i++;
	}
	printf("PATH[%d] %s |\n\n", i, path_array[i]);
	i = 0;
	while (array[i])
	{
		if (ft_strncmp(array[i], "cd", 3) == 0)
		{
			i += unbuilt_cd_syntax(array, i);
			if (i == -1)
				return (-1);
		}
		else if (ft_strncmp(array[i], "pwd", 4) == 0)
		{
			i += unbuilt_pwd_syntax(array, i);
		}
		else if (ft_strncmp(array[i], "env", 4) == 0)
		{
			i += unbuilt_env_syntax(array, i);
			if (i == -1)
				return (-1);
		}
		else if (ft_strncmp(array[i], "echo", 5) == 0)
		{
			i += unbuilt_echo_syntax(array, i);
		}
		else if (ft_strncmp(array[i], "exit", 5) == 0)
		{
			i += unbuilt_exit_syntax(array, i);
			if (i == -1)
				return (-1);
		}
		else if (ft_strncmp(array[i], "unset", 6) == 0)
		{
			i += unbuilt_unset_syntax(array, i);
		}
		else if (ft_strncmp(array[i], "export", 7) == 0)
		{
			i += unbuilt_export_syntax(array, i);
		}
		else if (list_words[i] == FILE_OR_COMMAND)
		{
			printf("Inbuilt \"%s\" not found. Looking for file...\n", array[i]);
			parser_check_file_path(path_array, array[i]);
		}
		if (array[i])
			i++;
	}
	i = 0;
	while (path_array[i])
	{
		free(path_array[i]);
		i++;
	}
	free(path_array);
	return (0);
}
