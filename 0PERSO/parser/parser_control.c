/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:58:14 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/07/08 15:27:04 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
WARNING : parser_control.c and parser_core.c DOES NOT HANDLE << EOF yet
*/

#include "../minishell.h"

void	parser_control(char	*line_read)
{
	char	**parsed_array;
	int		*list_words;
	int		i;

	parsed_array = parsing_megasplit_control(line_read);
	if (!parsed_array)
		return ;
	i = 0;
	while (parsed_array[i])
	{
		printf("[%d] %s\n", i, parsed_array[i]);
		i++;
	}
	printf("[%d] %s |\n", i, parsed_array[i]);
	/****************************************/
	/* Write << EOF control HERE */
	/****************************************/
	if ((check_token_syntax(parsed_array)) == -1)
	{
		i = 0;
		while (parsed_array[i])
		{
			free(parsed_array[i]);
			i++;
		}
		free(parsed_array);
		return ;
	}
	list_words = (int *)malloc((i + 1) * sizeof(int *));
	if (!list_words)
	{
		free(parsed_array);
		return ;
	}
	list_words[i] = END_OF_LIST;
	build_tokens_list(parsed_array, list_words);
	parsing_trimmer(parsed_array);
	printf("\nUNKNOWN\t\t -1\nEND_OF_LIST\t 0\nPIPE\t\t 1\nREDIR_OUT\t 2\nREDIR_IN\t 3\n");
	printf("APPEND_REDIR_OUT 4\nHERE_DOC\t 5\nFILE_OR_COMMAND\t 6\nARG_OR_OPTION\t 7\n\n");
	i = 0;
	while (parsed_array[i])
	{
		printf("{%d} [%d] %s\n", list_words[i], i, parsed_array[i]);
		i++;
	}
	printf("{%d} [%d] %s\n\n", list_words[i], i, parsed_array[i]);
	if ((check_file_syntax(parsed_array, list_words)) == -1)
		return ;
	free(list_words);
	i = 0;
	while (parsed_array[i])
	{
		free(parsed_array[i]);
		i++;
	}
	free(parsed_array);
	return ;
}
