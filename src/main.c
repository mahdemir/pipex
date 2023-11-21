/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mademir <mademir@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/18 14:38:32 by mademir       #+#    #+#                 */
/*   Updated: 2023/11/21 13:02:01 by mademir       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		infile;
	int		outfile;
	int		fds[2];
	pid_t	pid;

	if (argc != 5)
		err_msg(MSG_ARGUMENTS, NULL);
	if (pipe(fds) == -1)
		err_msg(MSG_PIPE, NULL);
	pid = fork();
	if (pid == -1)
		err_msg(MSG_FORK, NULL);
	infile = open(argv[1], O_RDONLY);
	if (infile == -1 && pid == 0)
		err_msg(MSG_FILE, argv[1]);
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, FULL_PERM);
	if (outfile == -1)
		err_msg(MSG_FILE, argv[4]);
	if (pid == 0)
		child_proces(argv, envp, infile, fds);
	wait(NULL);
	parent_proces(argv, envp, outfile, fds);
	return (0);
}
