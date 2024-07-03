/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:24:36 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/07/02 15:13:00 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

char		**mini_split(char *str, char c);
static char	*make_word(char *str, char c);

int	main(void)
{
	char	str[] = ":A:BC:DEF:GHIJ:KLMNO:PQRSTU:";
	char	c = ':';
	char	**checker;
	int		i;

	i = 0;
	checker = mini_split(str, c);
	printf("\n\n");
	while (i < 6)
	{
		printf("[%d] |%s|\n", i, checker[i]);
		free(checker[i]);
		i++;
	}
	free(checker);
	return (0);
}

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
			array[j] = make_word(str + i, c);
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

static char	*make_word(char *str, char c)
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
