/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:29:03 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/07/08 12:10:14 by lahlsweh         ###   ########.fr       */
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
