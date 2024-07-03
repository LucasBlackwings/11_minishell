/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minisplit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:57:15 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/07/03 14:12:42 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**mini_split(char *str, char c)
{
	int		num_words;
	char	**array;
	int		i;
	int		j;

	i = 0;
	num_words = 0;
	while (str[i])
	{
		if ((str[i] != c)
			&& (str[i + 1] == c || str[i + 1] == '\0'))
			num_words++;
		i++;
	}
	array = (char **)malloc((num_words + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			array[j] = mini_make_word(str + i, c);
			j++;
			while (str[i] && str[i] != c)
				i++;
		}
		if (str[i])
			i++;
	}
	array[j] = NULL;
	return (array);
}

char	*mini_make_word(char *str, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	word = (char *)malloc((i + 1) * sizeof(char));
	i = 0;
	while (str[i] && str[i] != c)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}
