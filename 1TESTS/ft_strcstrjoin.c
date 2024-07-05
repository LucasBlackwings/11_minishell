/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:44:50 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/07/03 13:27:08 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

char	*ft_strcstrjoin(const char *s1, const char c2, const char *s3);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t size);

int	main(void)
{
	char	s1[] = "/home/lahlsweh/bin";
	char	c2 = '/';
	char	s3[] = "grep";
	char	*path;

	path = ft_strcstrjoin(s1, c2, s3);
	printf("%s\n", path);
	free(path);
	return (0);
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
