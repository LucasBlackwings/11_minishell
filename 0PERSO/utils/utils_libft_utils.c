/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:29:03 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/07/08 14:20:49 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*malloc_ptr;

	if (nmemb == 0 || size == 0)
		return ((void *)malloc(0));
	if (size > 0)
	{
		if (nmemb > (size_t) - 1 / size)
			return (NULL);
	}
	malloc_ptr = (void *)malloc(nmemb * size);
	if (!malloc_ptr)
		return (NULL);
	ft_bzero(malloc_ptr, nmemb * size);
	return (malloc_ptr);
}

void	ft_bzero(void *s, size_t n)
{
	char	*s_ptr;

	s_ptr = (char *)s;
	while (n > 0)
	{
		*s_ptr = 0;
		s_ptr++;
		n--;
	}
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	i;

	src_len = 0;
	dst_len = 0;
	i = 0;
	while (src[src_len])
		src_len++;
	while (dst[dst_len])
		dst_len++;
	if (!size)
		return (src_len);
	while (src[i] && dst_len + i < size - 1)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	if (size <= dst_len)
		return (src_len + size);
	return (src_len + dst_len);
}

/* Compare str1 and str2 up to num characters
Returns (-1) if !str1 OR !str2 OR num < 1
Returns (1) if str1 != str2
Returns (1) if i < num AND one string still exists (while not the other)
	Thi way ft_strncmp("A", "AB", 2) == 1 AND ft_strncmp("A", "A", 2) == 0
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
