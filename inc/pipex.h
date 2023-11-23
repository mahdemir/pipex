/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mademir <mademir@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/18 14:39:03 by mademir       #+#    #+#                 */
/*   Updated: 2023/11/23 14:23:07 by mademir       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define FULL_PERM 0777
# define MSG_ARGUMENTS "\033[31mError:\033[0m invalid amount of arguments\n"
# define MSG_PIPE "\033[31mError:\033[0m cannot create pipe\n"
# define MSG_FORK "\033[31mError:\033[0m cannot fork process\n"
# define MSG_FILE "\033[31mError:\033[0m no such file or directory: "
# define MSG_COMMAND "\033[31mError:\033[0m command not found: "
# define MSG_COMMAND_EMPTY "\033[31mError:\033[0m command not found"

/********** LIBRARIES *********************************************************/

# include <sys/wait.h> // wait(), waitpid()
# include <fcntl.h> // open()
# include <stdio.h> // strerror()
# include <string.h> // perror()
# include "../libft/inc/libft.h" // <unistd.h>, <stdlib.h>, <stdarg.h>

/********** PROTOTYPES ********************************************************/

/* First command reads the input from the infile
 * and passes the output to the write-end(fd[1]) of the pipe. */
int	infile_to_pipe(char **argv, char **envp, int *fd);

/* Second command takes input from read-end(fd[0]) of the pipe
 * and passes the output to the output file. */
int	pipe_to_outfile(char **argv, char **envp, int *fd);

/* Simple error handling function that prints message to STDERR. */
void	err_msg(char *message, char *argv);

#endif
