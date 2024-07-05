/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:29:03 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/07/05 11:51:29 by lahlsweh         ###   ########.fr       */
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

char	*ft_strcstrjoin(const char *s1, const char c2, const char *s3)
{
	char	*calloc_ptr;
	int		s1_len;
	int		s3_len;

	if (!s1 || !s3)
		return (NULL);
	s1_len = 0;
	s3_len = 0;
	while (s1[s1_len])
		s1_len++;
	while (s3[s3_len])
		s3_len++;
	calloc_ptr = (char *)ft_calloc(s1_len + 1 + s3_len + 1, sizeof(char));
	if (!calloc_ptr)
		return (NULL);
	ft_strlcat(calloc_ptr, s1, s1_len + 1);
	calloc_ptr[s1_len] = c2;
	ft_strlcat(calloc_ptr, s3, s1_len + 1 + s3_len + 1);
	return (calloc_ptr);
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

/* Use to compare two strings s1 and s2
Returns (0) if s1=s2, return (>0) otherwise */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1_ptr;
	unsigned char	*s2_ptr;
	size_t			i;

	s1_ptr = (unsigned char *)s1;
	s2_ptr = (unsigned char *)s2;
	i = 0;
	if (n <= 0)
		return (0);
	while (s1_ptr[i] && s2_ptr[i] && i < (n - 1))
	{
		if (s1_ptr[i] != s2_ptr[i])
			return (s1_ptr[i] - s2_ptr[i]);
		i++;
	}
	return (s1_ptr[i] - s2_ptr[i]);
}

/* Use to compare two strings str1 and str2
Returns (0) if s1=s2, return (>0) otherwise */
int	ft_str_search_str(char *str1, char *str2)
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

/* Use to compare a char c with a string str 
Returns (1) if c is equal to any character in str
Returns (0) otherwise */
int	ft_c_search_str(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
