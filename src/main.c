/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 23:11:22 by joppe         #+#    #+#                 */
/*   Updated: 2023/03/18 16:40:26 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
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


int main(int argc, char *argv[], char *envp[])
{
	return (fork_test(argc, argv, envp));
}
