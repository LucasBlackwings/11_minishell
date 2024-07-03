/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:56:55 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/07/03 10:47:08 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
CURRENT PROGRAM DOES NOT HANDLE NORM
				DOES NOT HANDLE PROTECTIONS
No leak should be observed except in case of crashing unprotected functions

TODOLIST PROMPT :
Handle CTRL+C
Handle CTRL+D
Handle CTRL+\
*/

#include "minishell.h"

int	main(void)
{
	char	*prompt;
	char	*line_read;

	prompt = build_prompt_control();
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

	parsed_array = parsing_split_control(line_read);
	parsing_interpreter(parsed_array);
	i = 0;
	while (parsed_array[i])
	{
		free(parsed_array[i]);
		i++;
	}
	free(parsed_array);
	return ;
}
