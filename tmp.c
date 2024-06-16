/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:43:34 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/06/14 10:48:55 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <dirent.h>
#include <errno.h>
//#include <stropts.h>
#include <termios.h>
#include <curses.h>
#include <term.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <limits.h>
#include <linux/limits.h>

#include <string.h>

char	*ft_strcat(char *dst, const char *src);
int		ft_strcmp(const char *s1, const char *s2);

int	main(void)
{
	char	*input;
	char	*cwd;

	cwd = (char *)malloc(PATH_MAX * sizeof(char));
	while (1)
	{
		getcwd(cwd, PATH_MAX);
		input = readline(ft_strcat(cwd, "$ "));
		if (*input)
			add_history(input);
		printf("INPUT : %s\n", input);
		free(input);
	}
	rl_clear_history();
	free(cwd);
	return (0);
}

char	*ft_strcat(char *dst, const char *src)
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
	while (src[i])
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst);
}
