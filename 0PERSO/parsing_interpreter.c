/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_interpreter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 10:56:31 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/06/28 15:17:33 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*FEATURES LIST :


EACH COMMAND IN A PIPELINE RUNS IN A SUBSHELL
Subshells in Bash are processes that  provide an isolated environment for command execution.
They inherit the environment and exported variables from the parent shell but do not propagate changes back to the parent shell.
They also have their own process IDs, file descriptors, and trap commands, among other attributes. 
In minishell : Only '|' can create subshells. In real bash, more tokens can be used for that purpose.


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

void	parsing_interpreter(char **array)
{
	int	i;
	int	array_len;

	i = 0;
	while (array[i])
	{
		printf("[%d] %s | ", i, array[i]);
		i++;
	}
	printf("[%d] %s |\n", i, array[i]);
	array_len = i;
	printf("array_len : %d\n", array_len);
	if ((check_bad_token_syntax(array, array_len)) == 1)
		return ;
	return ;
}

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
>|		bash: syntax error near unexpected token `newline'		token '>|' at end of file (IMPLEMENT '|' INSTEAD)

|		bash: syntax error near unexpected token `|'			
||		bash: syntax error near unexpected token `||'			token '||' after other token (IMPLEMENT '|' INSTEAD)
|||		bash: syntax error near unexpected token `||'			token '||' after other token (IMPLEMENT '|' INSTEAD)
||||	bash: syntax error near unexpected token `||'			token '||' after other token (IMPLEMENT '|' INSTEAD)*/

int	check_bad_token_syntax(char **array, int array_len)
{
	int	i;

	i = 0;
	while (array[i] && array[i + 1])
	{
		if (array[i][0] == '|' || array[i][0] == '>' || array[i][0] == '<')
		{
			if (array[i + 1][0] == '>' && array[i + 1][1] == '>')
				return (printf("bash: syntax error near unexpected token `>>'\n"), 1);
			else if (array[i + 1][0] == '>')
				return (printf("bash: syntax error near unexpected token `>'\n"), 1);
			else if (array[i + 1][0] == '<' && array[i + 1][1] == '<')
				return (printf("bash: syntax error near unexpected token `<<'\n"), 1);
			else if (array[i + 1][0] == '<')
				return (printf("bash: syntax error near unexpected token `<'\n"), 1);
			else if (array[i + 1][0] == '|')
				return (printf("bash: syntax error near unexpected token `|'\n"), 1);
		}
		i++;
	}
	if (array[array_len - 1][0] == '>' || array[array_len - 1][0] == '<')
		return (printf("bash: syntax error near unexpected token `newline'\n"), 1);
	if (array[array_len - 1][0] == '|' && array_len == 1)
		return (printf("bash: syntax error near unexpected token `|'\n"), 1);
	return (0);
}
