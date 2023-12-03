/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mademir <mademir@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/18 19:45:31 by mademir       #+#    #+#                 */
/*   Updated: 2023/12/02 17:29:21 by mademir       ########   odam.nl         */
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
	ft_matrix_free((void **)paths, i);
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
	if (!*cmd)
		err_msg(MSG_COMMAND_EMPTY, argv, 127);
	if (access(*cmd, F_OK) == 0)
		path = *cmd;
	else
		path = path_finder(envp, cmd[0]);
	if (!path)
	{
		ft_matrix_free((void **)cmd, ft_matrix_height((void **)cmd));
		err_msg(MSG_COMMAND, argv, 127);
	}
	if (execve(path, cmd, envp) == -1)
		err_msg(MSG_COMMAND, argv, 127);
}

void	err_msg(char *message, char *argv, int code)
{
	ft_putstr_fd(message, 2);
	if (argv)
	{
		ft_putstr_fd(argv, 2);
		ft_putchar_fd('\n', 2);
	}
	exit(code);
}

void	infile_to_pipe(char **argv, char **envp, int *fd)
{
	pid_t	pid;
	int		infile;

	pid = fork();
	if (pid == -1)
		err_msg(MSG_FORK, NULL, 1);
	else if (pid == 0)
	{
		close(fd[0]);
		infile = open(argv[1], O_RDONLY);
		if (infile == -1)
			err_msg(MSG_FILE, argv[1], 1);
		dup2(infile, STDIN_FILENO);
		close(infile);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute(argv[2], envp);
	}
}

void	pipe_to_outfile(char **argv, char **envp, int *fd)
{
	pid_t	ppid;
	int		outfile;

	close(fd[1]);
	ppid = fork();
	if (ppid == -1)
		err_msg(MSG_FORK, NULL, 1);
	else if (ppid == 0)
	{
		outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, FULL_PERM);
		if (outfile == -1)
			err_msg(MSG_FILE, argv[4], 1);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
		execute(argv[3], envp);
	}
}
