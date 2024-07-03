/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_interpreter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 10:56:31 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/07/03 11:31:14 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*GRAMMAR RULES :

ANY '>' '>>' '<' '<<' followed by ANY '>' '>>' '<' '<<' will lead to syntax error
ANY single token '|' '>' '>>' '<' '<<' will lead to syntax error;
ANY command ending with '>' '>>' '<' '<<' will lead to syntax error.
ANY command starting with '|' will lead to syntax error;

||	is a bash token that must be ignored
<>	is a bash token that must be ignored
<<<	is a bash token that must be ignored
>|	is a bash token that must be ignored

>		bash: syntax error near unexpected token `newline'		token '>' at end of file
>>		bash: syntax error near unexpected token `newline'		token '>>' at end of file
<		bash: syntax error near unexpected token `newline'		token '<' at end of file
<<		bash: syntax error near unexpected token `newline'		token '<<' at end of file

>>>		bash: syntax error near unexpected token `>'			token '>' after other token
>>>|	bash: syntax error near unexpected token `>|'			token '>|' after other token (IMPLEMENT '>' INSTEAD)
<>|		bash: syntax error near unexpected token `|'			token '|' after other token (IMPLEMENT '>' INSTEAD)

>>>>	bash: syntax error near unexpected token `>>'			token '>>' after other token
>>>>|	bash: syntax error near unexpected token `>>'			token '>>' after other token
>>>>>	bash: syntax error near unexpected token `>>'			token '>>' after other token

><|		bash: syntax error near unexpected token `<'			token '<' after other token
<<<		bash: syntax error near unexpected token `newline'		token '<<<' at end of file (IMPLEMENT '<' INSTEAD)

<<<<<	bash: syntax error near unexpected token `<<'			token '<<' after other token
<<<<	bash: syntax error near unexpected token `<'			token '<' after other token (IMPLEMENT '<<' INSTEAD)
<<<<|	bash: syntax error near unexpected token `<'			token '<' after other token (IMPLEMENT '<<' INSTEAD)
<<<<<<	bash: syntax error near unexpected token `<<<'			token '<<<' after other token (IMPLEMENT '<<' INSTEAD)
	
<|		bash: syntax error near unexpected token `|'			token '|' after other token
>>|		bash: syntax error near unexpected token `|'			token '|' after other token
<<|		bash: syntax error near unexpected token `|'			token '|' after other token
<<<|	bash: syntax error near unexpected token `|'			token '|' after other token
>|		bash: syntax error near unexpected token `newline'		token '>|' at end of file (IMPLEMENT '|' INSTEAD)key=value

|		bash: syntax error near unexpected token `|'			
||		bash: syntax error near unexpected token `||'			token '||' after other token (IMPLEMENT '|' INSTEAD)
|||		bash: syntax error near unexpected token `||'			token '||' after other token (IMPLEMENT '|' INSTEAD)
||||	bash: syntax error near unexpected token `||'			token '||' after other token (IMPLEMENT '|' INSTEAD)


Commands that must handle 0 to ARG_MAX arguments :
echo	[-n] [STRING]...
export	name[=word]...
unset	name...

Commands that must handle 0 to 1 arguments :
exit	[n]
cd		[directory] // relative OR absolute path

Commands that takes no arguments :
pwd
env

CORRECT SYNTAXES :
ls > file1 -n > file2 -l > file3 -h

*/

#include "minishell.h"

#define END_OF_LIST 0
#define PIPE 1
#define REDIR_OUT 2 
#define REDIR_IN 3
#define APPEND_REDIR_OUT 4
#define HERE_DOC 5
#define FILE_OR_COMMAND 6
#define ARG_OR_OPTION 7
#define UNKNOWN -1

static int	check_token_syntax(char **array);
static void	build_tokens_list(char **array, int *list_words);
static void	parsing_trimmer(char **array);
static int	check_file_syntax(char **array, int *list_words);
static int	check_bad_inbuilts_syntax(char **array);
static int	lookup_file_path(char **array_of_paths, char *filename);

void	parsing_interpreter(char **array)
{
	int *list_words;
	int	i;
	
	i = 0;
	printf("\n");
	printf("END_OF_LIST 0\nPIPE 1\nREDIR_OUT 2\nREDIR_IN 3\nAPPEND_REDIR_OUT 4\nHERE_DOC 5\nFILE_OR_COMMAND 6\nARG_OR_OPTION 7\nUNKNOWN -1\n\n");
	while (array[i])
	{
		printf("[%d] %s\n", i, array[i]);
		i++;
	}
	printf("[%d] %s |\n", i, array[i]);
	if ((check_token_syntax(array)) == -1)
		return ;
	list_words = (int *)malloc((i + 1) * sizeof(int *));
	list_words[i] = END_OF_LIST;
	build_tokens_list(array, list_words);
	parsing_trimmer(array);
	i = 0;
	printf("\n");
	while (array[i])
	{
		printf("{%d} [%d] %s\n", list_words[i], i, array[i]);
		i++;
	}
	printf("{%d} [%d] %s\n\n", list_words[i], i, array[i]);
	if ((check_file_syntax(array, list_words)) == -1)
		return ;
	free(list_words);
	return ;
}

static int	check_token_syntax(char **array)
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

static void	build_tokens_list(char **array, int *list_words)
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

static void	parsing_trimmer(char **array)
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

static int	check_file_syntax(char **array, int *list_words)
{
	char	*path_env;
	char	**path_array;
	int		i;
	
	if ((check_bad_inbuilts_syntax(array)) == -1)
		return (-1);
	path_env = getenv("PATH");
	path_array = mini_split(path_env, ':');
	i = 0;
	while (path_array[i])
	{
		printf("[%d] %s\n", i, path_array[i]);
		i++;
	}
	printf("[%d] %s |\n", i, path_array[i]);
	i = 0;
	while (list_words[i])
	{
		if (list_words[i] == FILE_OR_COMMAND)
		{
			lookup_file_path(path_array, array[i]);
		}
		i++;
	}
	while (path_array[i])
	{
		free(path_array[i]);
		i++;
	}
	free(path_array);
	array = NULL;
	list_words = NULL;
	return (0);
}

static int	check_bad_inbuilts_syntax(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (array[i][0] == 'c' && array[i][1] == 'd' && array[i][2] == '\0')
		{
			i += unbuilt_cd_syntax(array, i);
			if (i == -1)
				return (-1);
		}
		else if (array[i][0] == 'p' && array[i][1] == 'w' && array[i][2] == 'd' && array[i][3] == '\0')
		{
			i += unbuilt_pwd_syntax(array, i);
		}
		else if (array[i][0] == 'e' && array[i][1] == 'n' && array[i][2] == 'v' && array[i][3] == '\0')
		{
			i += unbuilt_env_syntax(array, i);
			if (i == -1)
				return (-1);
		}
		else if (array[i][0] == 'e' && array[i][1] == 'c' && array[i][2] == 'h' && array[i][3] == 'o' && array[i][4] == '\0')
		{
			i += unbuilt_echo_syntax(array, i);FILEPATH[0] = /home/lahlsweh/.local/funcheck/host/
		}
		else if (array[i][0] == 'e' && array[i][1] == 'x' && array[i][2] == 'i' && array[i][3] == 't' && array[i][4] == '\0')
		{
			i += unbuilt_exit_syntax(array, i);
			if (i == -1)
				return (-1);
		}
		else if (array[i][0] == 'u' && array[i][1] == 'n' && array[i][2] == 's' && array[i][3] == 'e' && array[i][4] == 't' && array[i][5] == '\0')
		{
			i += unbuilt_unset_syntax(array, i);
		}
		else if (array[i][0] == 'e' && array[i][1] == 'x' && array[i][2] == 'p' && array[i][3] == 'o'
				&& array[i][4] == 'r' && array[i][5] == 't' && array[i][6] == '\0')
		{
			i += unbuilt_export_syntax(array, i);
		}
		if (array[i])
			i++;
	}
	return (0);
}

static int	lookup_file_path(char **array_of_paths, char *filename)
{
	char	*filepath;
	int		i;

	i = 0;
	while (array_of_paths[i])
	{
		filepath = ft_str3join(array_of_paths[i], "/", filename);
		printf("FILEPATH[%d] = %s\n", i, filepath);
		if (access(filepath, X_OK) == 0)
		{
			free(filepath);
			return (TRUE);
		}
		free(filepath);
		i++;
	}
	printf("%s: command not found\n", filename);
	return (FALSE);
}
