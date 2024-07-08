/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:53:22 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/07/08 11:38:09 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parser_check_file_path(char **array_of_paths, char *filename)
{
	char	*filepath;
	int		i;

	i = 0;
	while (array_of_paths[i])
	{
		filepath = ft_strcstrjoin(array_of_paths[i], '/', filename);
		if (access(filepath, X_OK) == 0)
		{
			printf("\nCommand %s found in : %s\n\n", filename, filepath);
			free(filepath);
			return (TRUE);
		}
		free(filepath);
		i++;
	}
	printf("%s: command not found\n", filename);
	return (FALSE);
}
