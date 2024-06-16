/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 15:50:37 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/06/16 15:55:14 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*make_word(char *str);

char	**split_minishell(char *str)
{
	int		i;
	int		num_words;
	char	**array;
	int		j;

	i = 0;
	num_words = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (str[i] == '\'')
		{
			i++;
			num_words++;
			while (str[i] && str[i] != '\'')
				i++;
			i++;
		}
		if (str[i] == '\"')
		{
			i++;
			num_words++;
			while (str[i] && str[i] != '\"')
				i++;
			i++;
		}
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
		{
			num_words++;
			while (str[i] && str[i] != ' ' && str[i] != '\t')
				i++;
		}
	}
	array = (char **)malloc((num_words + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (str[i] == '\'')
		{
			array[j] = make_word(str + i);
			j++;
			i++;
			while (str[i] && str[i] != '\'')
				i++;
		}
		if (str[i] == '\"')
		{
			array[j] = make_word(str + i);
			j++;
			i++;
			while (str[i] && str[i] != '\"')
				i++;
		}
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\'' && str[i] != '\"')
		{
			array[j] = make_word(str + i);
			j++;
			while (str[i] && str[i] != ' ' && str[i] != '\t')
			{
				i++;
			}
		}
		if (str[i])
			i++;
	}
	array[j] = NULL;
	return (array);
}

char	*make_word(char *str)
{
	int		i;
	int		quote_check;
	char	*word;

	i = 0;
	quote_check = 0;
	if (str[i] == '\'')
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		i++;
	}
	else if (str[i] == '\"')
	{
		i++;
		while (str[i] && str[i] != '\"')
			i++;
		i++;
	}
	else
	{
		while (str[i] && str[i] != ' ' && str[i] != '\t')
			i++;
	}
	word = (char *)malloc((i + 1) * sizeof(char));
	i = 0;
	if (str[i] == '\'')
	{
		word[i] = str[i];
		i++;
		while (str[i] && str[i] != '\'')
		{
			word[i] = str[i];
			i++;
		}
		word[i] = str[i];
		i++;
	}
	else if (str[i] == '\"')
	{
		word[i] = str[i];
		i++;
		while (str[i] && str[i] != '\"')
		{
			word[i] = str[i];
			i++;
		}
		word[i] = str[i];
		i++;
	}
	else
	{
		while (str[i] && str[i] != ' ' && str[i] != '\t')
		{
			word[i] = str[i];
			i++;
		}
	}
	word[i] = '\0';
	return (word);
}
