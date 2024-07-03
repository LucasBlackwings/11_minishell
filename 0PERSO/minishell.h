/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:35:06 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/07/03 10:45:02 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <dirent.h>
//#include <stropts.h>
# include <termios.h>
# include <curses.h> //  -lncurses ???
# include <term.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <readline/readline.h> // -lreadline 
# include <readline/history.h> // -lreadline 

# include <limits.h>
# include <linux/limits.h>

# define FALSE 0
# define TRUE 1

void	parser(char	*line_read);
char	*build_prompt_control(void);
char	**parsing_split_control(char *str);
void	parsing_interpreter(char **array);

char	**mini_split(char *str, char c);

int		unbuilt_echo_syntax(char **array, int i);
int		unbuilt_export_syntax(char **array, int i);
int		unbuilt_unset_syntax(char **array, int i);
int		unbuilt_exit_syntax(char **array, int i);
int		unbuilt_cd_syntax(char **array, int i);
int		unbuilt_pwd_syntax(char **array, int i);
int		unbuilt_env_syntax(char **array, int i);

void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_str3join(const char *s1, const char *s2, const char *s3);
size_t	ft_strlcat(char *dst, const char *src, size_t size);

#endif
