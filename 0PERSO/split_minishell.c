/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:09:24 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/06/19 15:14:46 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		count_words(char *str);
static char		*make_word(char *str);
static int		count_word_len(char *str);

char	**split_minishell_control(char *str)
{
	char	**array;
	int		num_words;
	int		i;
	int		j;

	num_words = count_words(str);
	array = (char **)malloc((num_words + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (str[i] == '|')
		{
			array[j] = make_word(str + i);
			i++;
			j++;
		}
		else if (str[i] == '>')
		{
			array[j] = make_word(str + i);
			i++;
			j++;
			if (str[i] == '>')
				i++;
		}
		else if (str[i] == '<')
		{
			array[j] = make_word(str + i);
			i++;
			j++;
			if (str[i] == '<')
				i++;
		}
		else if (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '|' && str[i] != '>' && str[i] != '<' && str[i] != '\0')
		{
			array[j] = make_word(str + i);
			j++;
			while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '|' && str[i] != '>' && str[i] != '<')
			{
				if (str[i] == '\'')
				{
					i++;
					while (str[i] && str[i] != '\'')
						i++;
				}
				if (str[i] == '\"')
				{
					i++;
					while (str[i] && str[i] != '\"')
						i++;
				}
				if (str[i])
					i++;
			}
		}
	}
	array[j] = NULL;
	return (array);
}

static int	count_words(char *str)
{
	int	num_words;
	int	i;

	num_words = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (str[i] && str[i] == '|')
		{
			i++;
			num_words++;
		}
		else if (str[i] && str[i] == '>')
		{
			i++;
			if (str[i] == '>')
				i++;
			num_words++;
		}
		else if (str[i] && str[i] == '<')
		{
			i++;
			if (str[i] == '<')
				i++;
			num_words++;
		}
		else if (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
		{
			while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '|' && str[i] != '>' && str[i] != '<')
			{
				if (str[i] == '\'')
				{
					i++;
					while (str[i] && str[i] != '\'')
						i++;
				}
				if (str[i] == '\"')
				{
					i++;
					while (str[i] && str[i] != '\"')
						i++;
				}
				if (str[i])
					i++;
			}
			num_words++;
		}
	}
	return (num_words);
}

static char	*make_word(char *str)
{
	char	*word;
	int		word_len;
	int		i;

	word_len = count_word_len(str);
	word = (char *)malloc((word_len + 1) * sizeof(char));
	i = 0;
	while (i < word_len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static int	count_word_len(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '|')
		i = 1;
	else if (str[i] == '>')
	{
		i = 1;
		if (str[i] == '>')
			i = 2;
	}
	else if (str[i] == '<')
	{
		i = 1;
		if (str[i] == '<')
			i = 2;
	}
	else
	{
		while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '|' && str[i] != '>' && str[i] != '<')
		{
			if (str[i] == '\'')
			{
				i++;
				while (str[i] && str[i] != '\'')
					i++;
			}
			if (str[i] == '\"')
			{
				i++;
				while (str[i] && str[i] != '\"')
					i++;
			}
			if (str[i])
				i++;
		}
	}
	return (i);
}
