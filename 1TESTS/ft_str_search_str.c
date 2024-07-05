/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_search_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:03:11 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/07/05 11:15:12 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_str_search_str(char *str1, char *str2);

int	main(void)
{
	char	str1[] = "ABCDEFGHJIKL";
	char	str2[] = "1234567890";
	int		checker;
	
	checker = ft_str_search_str(str1, str2);
	printf("checker = %d\n", checker);
	return (0);
}

/*ft_str_search_str search for the presence of any character from *chars in *str
Returns (1) if any character is found, returns (0) if no characters are found
See also : strchr(3) strstr(3)*/
int ft_str_search_str(char *str1, char *str2)
{
	int	i;
	int	j;

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
