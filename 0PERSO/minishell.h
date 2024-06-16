/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:35:06 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/06/16 15:52:12 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>
//#include <stropts.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <limits.h>
# include <linux/limits.h>

# define FALSE 0
# define TRUE 1

char	*build_prompt(char *user_env, char *session_manager_env, char *pwd_env);
char	**split_minishell(char *str);

#endif
