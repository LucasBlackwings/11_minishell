/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:35:06 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/06/28 10:11:25 by lahlsweh         ###   ########.fr       */
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
void	parsing_trimmer(char **parsed_array);
void	parsing_interpreter(char **parsed_array);

#endif
