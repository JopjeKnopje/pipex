/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 23:11:22 by joppe         #+#    #+#                 */
/*   Updated: 2023/03/21 00:18:25 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int fork_test(int argc, char *argv[], char *envp[])
{
	int fd[2];
	if (pipe(fd) == -1)
	{
		printf("error creating pipe\n");
		return 1;
	}


	pid_t pid = fork();
	if (pid == -1)
	{
		printf("error forking\n");
		return 1;
	}

	// Child writes to pipe
	if (pid == 0)
	{
		printf("created child with pid %d\n", pid);
		fflush(stdout);
		// dup2 close fd[1] and redirect STDOUT_FILENO to fd[1]
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);

		int ret = execve("/usr/bin/ls", argv, envp);
		if (ret == -1)
		{
			printf("execve error\n");
			return EXIT_FAILURE;
		}
	}
	// Parent reads from pipe
	else
	{
		close(fd[1]);
		printf("created parent with pid %d\n", pid);
		char *line = get_next_line(fd[0]);
		while (line) {
			printf("data from pipe [%s]\n", line);
			line = get_next_line(fd[0]);	
		}
		close(fd[0]);
	}
	return 0;
}


char *find_path(char *envp[])
{
	int i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH", envp[i], ft_strlen("PATH")))
			return (envp[i]);
		i++;
	}
	return (NULL);
}

char **split_path(char *s)
{
	char	**paths;
	char	*tmp;
	
	paths = ft_split(s, ':');

	tmp = ft_substr(paths[0], 5, ft_strlen(paths[0]) - 5);
	free(paths[0]);
	paths[0] = tmp;

	int i = 0;
	while (paths[i]) 
	{
		paths[i] = ft_strjoin_free(paths[i], "/");
		i++;
	}

	return (paths);
}

void	free_split(char **s_split)
{
	int	i;

	i = 0;
	while (s_split[i])
	{
		free(s_split[i]);
		i++;
	}
	free(s_split);
}

int run_cmd(char *argv[], char *envp[], char *cmd)
{
	int i = 0;
	int ret;
	char *path;
	char **paths;


	path = find_path(envp);
	paths = split_path(path);

	// printf("running [%s] with argv [%s]\n", )

	i = 1;
	while (paths[i]) 
	{
		paths[i] = ft_strjoin_free(paths[i], cmd);
		ret = execve(paths[i], argv, envp);
		printf("failed running execve with paths[%d] [%s]\n", i, paths[i]);
		// fflush(stdout);
		i++;
	}
	printf("execve failed\n");
	free_split(paths);
	return 0;
}


int pipex(int argc, char *argv[], char *envp[])
{
	if (!argv[1])
		return 0;
	char **args = parse_args(argv);

	print_split(args);

	int pid;

	int i = 0;
	while (args[i])
	{
		long delim = ft_strchr(args[i], ' ') - args[i];
		char *cmd = ft_substr(args[i], 0, delim);

		argv = ft_split(args[i], ' ');
		pid = fork();
		if (pid == 0)
		{
			run_cmd(argv, envp, cmd);
		}
		else {
			// wait otherwise the forks will run simultaneously and the printed output
			// will not be correct.
			waitpid(pid, NULL, 0);
		}
		free_split(argv);
		i++;
	}
	free_split(args);

	// for running in neovim terminal thing.
	fflush(stdout);
	return (0);
}

int main(int argc, char *argv[], char *envp[])
{
	// TODO: Parse all the arguments
	int fd_input = open(argv[1], O_RDONLY);
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	// TODO: Maybe use O_APPEND?
	int fd_output = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC,  mode);

	int fd_pipe[2];
	pipe(fd_pipe);

	if (fd_output == -1)
	{
		printf("Error with fd_output\n");
	}

	int pid = fork();

	int exec_return = 0;
	if (pid == 0)
	{
		close(fd_output);
		close(fd_pipe[0]);

		// Duplicate FD to FD2, closing FD2 and making it open on the same file.  
		dup2(fd_input, STDIN_FILENO);
		dup2(fd_pipe[1], STDOUT_FILENO);
		char *args[] = {
			"cat",
			NULL
		};
		exec_return = execve("/usr/bin/cat", args, envp);
		if (exec_return == -1)
		{
			printf("execve failed\n");
			return EXIT_FAILURE;
		}
	}
	else {
		close(fd_input);
		close(fd_output);
		close(fd_pipe[1]);

		char *line = get_next_line(fd_pipe[0]);
		while (line) 
		{
			printf("data from pipe [%s]\n", line);
			free(line);
			line = get_next_line(fd_pipe[0]);
		}
		free(line);
		close(fd_pipe[0]);
		waitpid(pid, NULL, 0);
	}
}
