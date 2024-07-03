/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:56:55 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/07/03 13:07:35 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			parser_control(line_read);
		}
		if (line_read)
			free(line_read);
	}
	free(prompt);
	return (0);
}
