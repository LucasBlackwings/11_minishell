/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_interpreter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 10:56:31 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/06/29 13:29:24 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
FEATURES LIST :


EACH COMMAND IN A PIPELINE RUNS IN A SUBSHELL
Subshells in Bash are processes that  provide an isolated environment for command execution.
They inherit the environment and exported variables from the parent shell but do not propagate changes back to the parent shell.
They also have their own process IDs, file descriptors, and trap commands, among other attributes. 
In minishell : Only '|' can create subshells. In real bash, more tokens can be used for that purpose.

GRAMMAR RULES :

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
>|		bash: syntax error near unexpected token `newline'		token '>|' at end of file (IMPLEMENT '|' INSTEAD)

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
*/

#include "minishell.h"

static int	check_bad_token_syntax(char **array, int array_len);
static int	check_bad_inbuilts_syntax(char **array);

void	parsing_interpreter(char **array)
{
	int	i;
	int	array_len;

	i = 0;
	while (array[i])
	{
		printf("[%d] %s\n", i, array[i]);
		i++;
	}
	printf("[%d] %s |\n", i, array[i]);
	array_len = i;
	printf("array_len : %d\n", array_len);
	if ((check_bad_token_syntax(array, array_len)) == -1)
		return ;
	if ((check_bad_inbuilts_syntax(array)) == -1)
		return ;
	return ;
}

int	check_bad_token_syntax(char **array, int array_len)
{
	int	i;

	i = 0;
	if (array_len == 0)
		return (0);
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
	if (array[array_len - 1][0] == '>' || array[array_len - 1][0] == '<')
		return (printf("bash: syntax error near unexpected token `newline'\n"), -1);
	if (array[array_len - 1][0] == '|' && array_len == 1)
		return (printf("bash: syntax error near unexpected token `|'\n"), -1);
	return (0);
}

int	check_bad_inbuilts_syntax(char **array)
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
			i += unbuilt_echo_syntax(array, i);
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
		else if (array[i][0] == 'e' && array[i][1] == 'x' && array[i][2] == 'p'
				&& array[i][3] == 'o' && array[i][4] == 'r' && array[i][5] == 't' && array[i][6] == '\0')
		{
			i += unbuilt_export_syntax(array, i);
		}
		if (array[i])
			i++;
	}
	return (1);
}
