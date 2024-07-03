/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:35:06 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/07/03 14:22:39 by lahlsweh         ###   ########.fr       */
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

/* UTILS minishell */
char	*ft_strcstrjoin(const char *s1, const char c2, const char *s3);

/* UTILS libft*/
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
char	**mini_split(char *str, char c);
char	*mini_make_word(char *str, char c);
//char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);

#endif
