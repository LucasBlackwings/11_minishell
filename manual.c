https://user-images.githubusercontent.com/68693691/193665518-0c0c7fec-38a9-4f6c-91ca-fef606abfb0d.png



/*Funny commands :
"e"'ch'"o" '-n' 't'"es"'t'1 test2 > 'exp'"ort" test3 test4 < u'n's"e"t t'es't"5" 'te's"t6" >> e'x'i"t" 255 | 'c'"d" .. >> 'pw'"d" < e'n'"v"
> grep echo grep && < grep grep grep | cat
grep < output -V < output2 -E < output3 -i
grep > output -V > output2 -E > output3 -i
> test1 < test2 >> test3 < test4 | test5
*/

/*****************************************************************************************************************************************/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <dirent.h>
#include <errno.h>
#include <stropts.h>
#include <termios.h>
#include <curses.h>
#include <term.h>

#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>

/*****************************************************************************************************************************************/

/* BASIC FUNCTIONS */

int		close(int fildes);
void	exit(int status);
void	free(void *ptr);
void	*malloc(size_t size);
int		open(const char *path, int oflag, ...);
void	perror(const char *s);
int		printf(const char *format, ...);
ssize_t	read(int fildes, void *buf, size_t nbyte);
char	*strerror(int errnum);
ssize_t	write(int fildes, const void *buf, size_t nbyte);

/*****************************************************************************************************************************************/

/* PIPEX : PROCESSES & FILE EXECUTION */

int		access(const char *path, int amode); // determine accessibility of a file descriptor
int		dup(int fildes); // duplicate an open file descriptor
int		dup2(int fildes, int fildes2); // duplicate an open file descriptor
pid_t	fork(void); // create a new process
pid_t	wait(int *stat_loc); // wait for a child process to stop or terminate
pid_t	waitpid(pid_t pid, int *stat_loc, int options); // wait for a child process to stop or terminate
int		pipe(int fildes[2]); // create an interprocess channel
int		execve(const char *path, char *const argv[], char *const envp[]); // execute a file
int		unlink(const char *path); // remove a directory entry


/* PROCESS related */

pid_t	wait3(int *wstatus, int options, struct rusage *rusage); // man 2 wait3 - wait for process to change state, BSD style
pid_t	wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage); // man 2 wait4 - wait for process to change state, BSD style

/*****************************************************************************************************************************************/

/* MINITALK : SIGNALS */

void	(*signal(int sig, void (*func)(int)))(int); // signal management
int		sigaddset(sigset_t *set, int signum); // POSIX signal set operations
int		sigemptyset(sigset_t *set); // POSIX signal set operations
int		sigaction(int sig, const struct sigaction *restrict act, struct sigaction *restrict oact); // examine and change a signal action
int		kill(pid_t pid, int sig); // send a signal to a process or a group of processes

/*****************************************************************************************************************************************/

/* FILE related */

#include <sys/stat.h>

int		fstat(int fildes, struct stat *buf); // get file status
int		stat(const char *restrict path, struct stat *restrict buf); // get file status
int		lstat(const char *restrict path, struct stat *restrict buf); // get file status

/*****************************************************************************************************************************************/

/* DIRECTORY related */

#include <unistd.h>

char	*getcwd(char *buf, size_t size); // get current working directory
int		chdir(const char *path); // change working directory


#include <sys/types.h>
#include <dirent.h>

DIR				*opendir(const char *name); // open a directory
struct	dirent	*readdir(DIR *dirp); // read a directory
int				closedir(DIR *dirp); // close a directory

/*****************************************************************************************************************************************/

/* terminal (TTY) related */

#include <unistd.h>

int		isatty(int fd); // test whether a file descriptor refers to a terminal
char	*ttyname(int fd); // return name of a terminal
int		ttyslot(void); // find the slot of the current user's terminal in some file


#include <termios.h>
#include <unistd.h>

int		tcgetattr(int fd, struct termios *termios_p); // get and set terminal attributes, line control, get and set baud rate
int		tcsetattr(int fd, int optional_actions, const struct termios *termios_p); // get and set terminal attributes, line control, get and set baud rate

/*****************************************************************************************************************************************/

/* CURSES */

#include <curses.h>
#include <term.h>

int		tgetent(char *bp, const char *name); // curses emulation of termcap
int		tgetflag(const char *id); // curses emulation of termcap
int		tgetnum(const char *id); // curses emulation of termcap
char	*tgetstr(const char *id, char **area); // curses emulation of termcap
char	*tgoto(const char *cap, int col, int row); // curses emulation of termcap
int		tputs(const char *str, int affcnt, int (*putc)(int)); // curses interfaces to terminfo database

/*****************************************************************************************************************************************/

/* MISCELLANIA */

#include <stropts.h>

int		ioctl(int fildes, int request, ... /* arg */); // control a STREAMS device (STREAMS)


#include <stdlib.h>

char	*getenv(const char *name); // get an environment variable


/*****************************************************************************************************************************************/

/* READLINE & HISTORY */

https://tiswww.case.edu/php/chet/readline/rltop.html

https://tiswww.case.edu/php/chet/readline/readline.html
https://tiswww.case.edu/php/chet/readline/history.html
https://tiswww.case.edu/php/chet/readline/rluserman.html

#include <stdio.h>
#include <readline/readline.h> // man 3 readline
#include <readline/history.h> // man 3 history

char	*readline(const char *prompt);
	readline will read a line from the terminal and return it, using prompt
	as a prompt.  If prompt is NULL or the empty string, no prompt  is  is_
	sued.   The  line returned is allocated with malloc(3); the caller must
	free it when finished.  The line returned has  the  final  newline  re_
	moved, so only the text of the line remains.

	readline  offers  editing  capabilities  while the user is entering the
	line.  By default, the line editing commands are similar  to  those  of
	emacs.  A vi-style line editing interface is also available.

	This  manual  page describes only the most basic use of readline.  Much
	more functionality is available; see The GNU Readline Library  and  The
	GNU History Library for additional information. 

int		rl_on_new_line (void); // LOCAL MAN NOT FOUND
Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline. 

void	rl_replace_line (const char *text, int clear_undo); // LOCAL MAN NOT FOUND
Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible.
If clear_undo is non-zero, the undo list associated with the current line is cleared. 

void	rl_redisplay (void); // LOCAL MAN NOT FOUND
Change what-s displayed on the screen to reflect the current contents of rl_line_buffer. 

void	add_history (const char *string);
	Place string at the end of the history list.  The associated data field
	(if  any) is set to NULL.  If the maximum number of history entries has
	been set using stifle_history(), and the new number of history  entries
	would exceed that maximum, the oldest history entry is removed.

void	rl_clear_history (void); // LOCAL MAN NOT FOUND
Clear the history list by deleting all of the entries, in the same manner as the History library-s clear_history() function.
This differs from clear_history because it frees private data Readline saves in the history list.


/*****************************************************************************************************************************************/
