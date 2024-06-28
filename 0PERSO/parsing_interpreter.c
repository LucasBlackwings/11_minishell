/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_interpreter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 10:56:31 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/06/26 15:35:58 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
FEATURES LIST :


EACH COMMAND IN A PIPELINE RUNS IN A SUBSHELL
Subshells in Bash are processes that  provide an isolated environment for command execution.
They inherit the environment and exported variables from the parent shell but do not propagate changes back to the parent shell.
They also have their own process IDs, file descriptors, and trap commands, among other attributes. 
In minishell : Only '|' can create subshells. In real bash, more tokens can be used for that purpose.

ANY syntax error will return prompt before executing anything, even if part of COMMAND is valid;
ANY single token '|' '>' '>>' '<' '<<' will lead to syntax error;
ANY command starting with '|' will lead to syntax error;
ANY command ending with '|' will change prompt to "> " and wait for further input to complete it;
ANY command ending with '>' '>>' '<' '<<' will lead to syntax error.

parsed_array[0] == "<"    parsed_array[1] == PATH
	PATH will remain unchanged;
	Command will fail if : [PATH does not exist] OR [PATH permissions = {000 to 333}].

parsed_array[0] == "<"    parsed_array[1] == PATH    parsed_array[2] == COMMAND
	If both PATH and COMMAND exists, execute COMMAND. PATH will remain unchanged;
	Command will fail if : [PATH does not exist] OR [COMMAND does not exist] OR [PATH permissions = {000 to 333}].

parsed_array[0] == "<<"    parsed_array[1] == DELIMITER
	"<<" opens heredoc. It must be followed by DELIMITER .DELIMITER can be anything, even empty quotes;
	If DELIMITER is '' or "", DEMILITER is considered to be '\n'. both '' and "" can handle multi-character delimiters;
	If '', heredoc content is treated as literal text. If "", heredoc behaves as if it were part of the normal shell script,
		allowing for variable expansion and command substitution;
		Default behaviour behaves as if shell script, meaning everything NOT '' will behave as if ""

parsed_array[0] == ">"    parsed_array[1] == FILEPATH
	All FILEPATH content will be erased;
	Command will fail if : [FILEPATH does not exist] OR [FILEPATH is not a file] OR [FILEPATH permissions = {000 to 111}].

parsed_array[0] == ">"    parsed_array[1] == FILEPATH    parsed_array[2] == COMMAND
	If both FILEPATH and COMMAND exists, execute COMMAND and writes output into FILEPATH;
	If FILEPATH does not exist, create FILEPATH and writes output into it;
	Command will fail if : [FILEPATH is not a file] OR [COMMAND does not exist] OR [FILEPATH permissions = {000 to 111}].

">>" behaves same as ">" but appends output instead of overwrite.


echo with option -n
cd with only a relative or absolute path
pwd with no options
export with no options
unset with no options
env with no options or arguments
exit with no options
*/

#include "minishell.h"

void	parsing_interpreter(char **parsed_array)
{
	int	i;
	int	array_size;

	i = 0;
	while (parsed_array[i])
	{
		printf("[%d] %s\n", i, parsed_array[i]);
		i++;
	}
	printf("[%d] %s\n", i, parsed_array[i]);
	array_size = i;
	printf("array_size = %d\n", array_size);
	i = 0;
	return ;
}
