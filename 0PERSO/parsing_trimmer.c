/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_trimmer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:11:40 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/06/29 13:40:56 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
TODOLIST :

Single quoting does not handle escape characters neither $
Double quoting should handle escape characters, $variable and $(function)
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
