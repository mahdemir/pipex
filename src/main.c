/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mademir <mademir@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/18 14:38:32 by mademir       #+#    #+#                 */
/*   Updated: 2023/12/02 16:23:47 by mademir       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fds[2];
	int		status;

	if (argc != 5)
		err_msg(MSG_ARGUMENTS, NULL, 1);
	if (pipe(fds) == -1)
		err_msg(MSG_PIPE, NULL, 1);
	infile_to_pipe(argv, envp, fds);
	pipe_to_outfile(argv, envp, fds);
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}
