/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:35:06 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/07/08 13:36:00 by lahlsweh         ###   ########.fr       */
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

/* build_tokens_list() Macros */
# define END_OF_LIST 0
# define PIPE 1
# define REDIR_OUT 2 
# define REDIR_IN 3
# define APPEND_REDIR_OUT 4
# define HERE_DOC 5
# define FILE_OR_COMMAND 6
# define ARG_OR_OPTION 7
# define UNKNOWN -1

// printf_error() macros */
# define ERR_PIPE 11
# define ERR_REDIR_OUT 12 
# define ERR_REDIR_IN 13
# define ERR_APPEND_REDIR_OUT 14
# define ERR_HERE_DOC 15
# define ERR_NEWLINE 16
# define ERR_CD_ARGS 17
# define ERR_ENV_ARGS 18
# define ERR_EXIT_ARGS 19

/* PROMPT */
char	*build_prompt_control(void);
char	*trim_pwd_env_if_home_user(char	*user_env, char *pwd_env);
char	*trim_session_manager_env(void);
int		count_prompt_len(char *user_env, char *session_manager_env, char *pwd_env);
char	*build_prompt(char *user_env, char *session_manager_env, char *pwd_env, int prompt_len);

/* PARSER control*/
void	parser_control(char	*line_read);

/* PARSER megasplit */
char	**parsing_megasplit_control(char *str);
int		count_words(char *str);
char	*make_word(char *str);
int		count_word_len(char *str);

/* PARSER core */
int		check_token_syntax(char **array);
void	build_tokens_list(char **array, int *list_words);
void	parsing_trimmer(char **array);
int		check_file_syntax(char **array, int *list_words);

/* PARSER inbuilts syntax */
int		unbuilt_cd_syntax(char **array, int i);
int		unbuilt_pwd_syntax(char **array, int i);
int		unbuilt_env_syntax(char **array, int i);
int		unbuilt_echo_syntax(char **array, int i);
int		unbuilt_exit_syntax(char **array, int i);
int		unbuilt_unset_syntax(char **array, int i);
int		unbuilt_export_syntax(char **array, int i);

/* PARSER utils */
int		parser_check_file_path(char **array_of_paths, char *filename);

/* UTILS libft*/
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_strncmp(const char *str1, const char *str2, const int num);

/* UTILS minishell */
char	*ft_strcstrjoin(const char *str1, const char char2, const char *str3);
int		ft_strcmp(const char *str1, const char *str2);
int		str_search_str(const char *str1, const char *str2);
int		str_search_c(const char *str1, const char char2);

/* UTILS minisplit */
char	**mini_split(char *str, char c);
char	*mini_make_word(char *str, char c);

/* UTILS print_errors */
void	printf_error(int status);

#endif
