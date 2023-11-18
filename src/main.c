/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mademir <mademir@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/18 14:38:32 by mademir       #+#    #+#                 */
/*   Updated: 2023/11/18 17:23:56 by mademir       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		status;
	pid_t	pid;

	if (argc != 5)
		err_msg();
	if (pipe(fd) == -1)
		err_msg();
	pid = fork();
	if (pid == -1)
		err_msg();
	if (pid == 0)
		// run child take opens infile
	waitpid(pid, &status, 0);
	// run parent that takes output of child en put his own output to in file
	return (0);	
}
