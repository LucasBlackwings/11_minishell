/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_megasplit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:09:24 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/07/05 13:04:20 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**parsing_megasplit_control(char *str)
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
		else if (str[i] && ft_c_search_str(str[i], " \t|><") == 0)
		{
			array[j] = make_word(str + i);
			j++;
			while (str[i] && ft_c_search_str(str[i], " \t|><") == 0)
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

int	count_words(char *str)
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
		else if (str[i] && str[i] != ' ' && str[i] != '\t')
		{
			while (str[i] && ft_c_search_str(str[i], " \t|><") == 0)
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

char	*make_word(char *str)
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

int	count_word_len(char *str)
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
		while (str[i] && ft_c_search_str(str[i], " \t|><") == 0)
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
