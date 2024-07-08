/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:24:35 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/07/08 12:23:31 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_strncmp(const char *str1, const char *str2, const int num);

int	main(void)
{
	//char	str1[] = ">>";
	//char	str2[] = "ABCDE";
	int		checker;
	checker = ft_strncmp(">>", ">>", 3);
	printf("checker : %d\n", checker);
	return (0);
}

/* Compare str1 and str2 up to num characters
Returns (-1) if !str1 OR !str2 OR num < 1
Returns (1) if str1 != str2
Returns (1) if i < num AND one string still exists (while not the other)
	Thi way ft_strncmp("A", "AB", 2) == 1 AND  ft_strncmp("A", "A", 2) == 0
Returns (0) otherwise*/
int	ft_strncmp(const char *str1, const char *str2, const int num)
{
	int	i;

	if (!str1 || !str2 || num < 1)
		return (-1);
	i = 0;
	while (str1[i] && str2[i] && i < num)
	{
		if (str1[i] != str2[i])
			return (1);
		i++;
	}
	if (i < num && ((!str1[i] && str2[i]) || (str1[i] && !str2[i])))
		return (1);
	return (0);
}
