/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mademir <mademir@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/18 14:38:32 by mademir       #+#    #+#                 */
/*   Updated: 2023/11/22 16:05:25 by mademir       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fds[2];

	if (argc != 5)
		err_msg(MSG_ARGUMENTS, NULL);
	if (pipe(fds) == -1)
		err_msg(MSG_PIPE, NULL);
	child_proces(argv, envp, fds);
	parent_proces(argv, envp, fds);
	close(fds[0]);
	close(fds[1]);
	return (0);
}
