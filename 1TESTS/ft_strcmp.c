/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 10:54:34 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/07/05 10:43:46 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>

int	ft_strcmp(char *s1, char *s2);

int	main(void)
{
	char	s1[] = "echol";
	char	s2[] = "echo";
	char	s3[] = "echol";
	char	s4[] = "echo";

	printf("s1[] = %s\ns2[] = %s\n", s1, s2);
	printf("   strcmp() returns : %d\n", strcmp(s1, s2));
	printf("ft_strcmp() returns : %d\n", ft_strcmp(s3, s4));
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		else
		{
			i++;
		}
	}
	return (0);
}
