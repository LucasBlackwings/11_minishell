/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:56:55 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/06/16 15:54:36 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TODOLIST PROMPT :
Handle CTRL+C
Handle CTRL+D
Handle CTRL+\

DONELIST PROMPT :
Build prompt (usename + @ + PC ID + PATH + "$ \0")
basic readline
add_history only if line_read is not empty
*/

#include "minishell.h"

void	parser(char	*line_read);

int	main(void)
{
	char	*user_env;
	char	*session_manager_env;
	char	*pwd_env;
	char	*prompt;
	char	*line_read;

	user_env = getenv("USER");
	session_manager_env = getenv("SESSION_MANAGER");
	pwd_env = getenv("PWD");
	prompt = build_prompt(user_env, session_manager_env, pwd_env);
	while (1)
	{
		line_read = readline(prompt);
		if (*line_read)
		{
			add_history(line_read);
			parser(line_read);
		}
		if (line_read)
			free(line_read);
	}
	free(prompt);
	return (0);
}

void	parser(char	*line_read)
{
	char	**parsed_array;
	int		i;

	parsed_array = split_minishell(line_read);
	i = 0;
	while (parsed_array[i])
	{
		printf("[%d] %s\n", i, parsed_array[i]);
		free(parsed_array[i]);
		i++;
	}
	free(parsed_array);
	return ;
}
