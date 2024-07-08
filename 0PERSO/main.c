/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:56:55 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/07/08 15:32:31 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*prompt;
	char	*line_read;

	prompt = build_prompt_control();
	if (!prompt)
		return (-1);
	while (1)
	{
		line_read = readline(prompt);
		if (!line_read)
			return (free(prompt), -1);
		if (*line_read)
		{
			add_history(line_read);
			parser_control(line_read);
		}
		if (line_read)
			free(line_read);
	}
	free(prompt);
	return (0);
}

// USE THIS TO FUNCHECK
/*int	main(int argc, char **argv)
{
	char	*prompt;

	if (argc != 2 || !argv[1][0])
		return (0);
	prompt = build_prompt_control();
	if (!prompt)
		return (-1);
	add_history(argv[1]);
	parser_control(argv[1]);
	free(prompt);
	return (0);
}*/
