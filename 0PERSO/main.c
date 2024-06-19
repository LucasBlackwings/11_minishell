/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:56:55 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/06/19 15:14:44 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TODOLIST PROMPT :
Handle CTRL+C
Handle CTRL+D
Handle CTRL+\

*/

#include "minishell.h"

void	parser(char	*line_read);

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

	parsed_array = split_minishell_control(line_read);
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
