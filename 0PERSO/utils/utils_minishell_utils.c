/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:22:43 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/07/08 13:35:41 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* The following functions behaves depending on returned data type :
If returns (char *) : (NULL) indicates error, (str) indicates success
If returns (int) : (-1) indicates error, (0) indicates success, (1) indicates failure */

/* Merge str1, char2 and str3 into merged_str
The merge order is str1 first, then char2, then str3
Returns (NULL) if !str1 OR !char2 OR !str3
Returns (NULL) if malloc() fails
Returns (merged_str) otherwise */
char	*ft_strcstrjoin(const char *str1, const char char2, const char *str3)
{
	int		str1_len;
	int		str3_len;
	char	*merged_str;

	if (!str1 || !char2 || !str3)
		return (NULL);
	str1_len = 0;
	str3_len = 0;
	while (str1[str1_len])
		str1_len++;
	while (str3[str3_len])
		str3_len++;
	merged_str = (char *)ft_calloc(str1_len + 1 + str3_len + 1, sizeof(char));
	if (!merged_str)
		return (NULL);
	ft_strlcat(merged_str, str1, str1_len + 1);
	merged_str[str1_len] = char2;
	ft_strlcat(merged_str, str3, str1_len + 1 + str3_len + 1);
	return (merged_str);
}

/* Compare str1 and str2
Returns (-1) if !str1 OR !str2
Returns (1) if str1 != str2
Returns (1) if one string is longer than the other
Returns (0) if str1 == str2 */
int	ft_strcmp(const char *str1, const char *str2)
{
	int	i;

	if (!str1 || !str2)
		return (-1);
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (1);
		i++;
	}
	if ((str1[i] && !str2[i]) || (!str1[i] && str2[i]))
		return (1);
	return (0);
}

/* Compare str1 and str2
Returns (-1) if !str1 OR !str2
Returns (1) if any character from str2 is found in str1
Returns (0) otherwise*/
int	str_search_str(const char *str1, const char *str2)
{
	int	i;
	int	j;

	if (!str1 || !str2)
		return (-1);
	i = 0;
	while (str1[i])
	{
		j = 0;
		while (str2[j])
		{
			if (str1[i] == str2[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

/* Use to compare a char c with a string str 
Returns (1) if any character in str1 is equal to char2
Returns (0) otherwise */
int	str_search_c(const char *str1, const char char2)
{
	int	i;

	if (!str1)
		return (-1);
	i = 0;
	while (str1[i])
	{
		if (str1[i] == char2)
			return (1);
		i++;
	}
	return (0);
}
