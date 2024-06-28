/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_trimmer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:11:40 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/06/28 12:18:27 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This feature is a prototype. It may or may not be removed lated.
Do not add more functions in this file.
*/

#include "minishell.h"

/*
This function trims all quotes and double wquotes from each words in array
And adjust word size (position of '\0') accordingly
*/

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
	return ;
}
