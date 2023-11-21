/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mademir <mademir@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/18 19:45:31 by mademir       #+#    #+#                 */
/*   Updated: 2023/11/21 16:47:38 by mademir       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Check if path to command exists */
static char	*path_finder(char **envp, char *cmd)
{
	int		i;
	char	**paths;
	char	*cmd_path;
	char	*path_slash;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	paths = ft_split(&envp[i][5], ':');
	i = 0;
	while (paths[i])
	{
		path_slash = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(path_slash, cmd);
		free(path_slash);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		else
			free(cmd_path);
		i++;
	}
	ft_matrix_free((void **)paths);
	return (NULL);
}

/* Function that handles the execution of commands */
static void	execute(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	if (!cmd)
		return ;
	path = path_finder(envp, cmd[0]);
	if (!path)
	{
		ft_matrix_free((void **)cmd);
		err_msg(MSG_COMMAND, argv);
	}
	if (execve(path, cmd, envp) == -1)
		err_msg(MSG_COMMAND, argv);
}

void	err_msg(char *message, char *argv)
{
	ft_putstr_fd(message, 2);
	if (argv)
	{
		ft_putstr_fd(argv, 2);
		ft_putchar_fd('\n', 2);
	}
	exit(EXIT_FAILURE);
}

void	child_proces(char **argv, char **envp, int infile, int *fd)
{
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	execute(argv[2], envp);
}

void	parent_proces(char **argv, char **envp, int outfile, int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[1]);
	execute(argv[3], envp);
}
