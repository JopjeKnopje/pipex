/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   processes.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboeve <marvin@42.fr>                        +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/01 10:47:39 by jboeve        #+#    #+#                 */
/*   Updated: 2023/05/02 15:58:47 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// Currently supports only 2 cmds
static int	redirect_fd(t_pipex *pipex, unsigned int cmd_index)
{
	// the first index
	if (!cmd_index)
	{
		printf("redirecting file to stdin...\n");

		// dup2(oldfd, newfd)
		dup2(pipex->files[READ_END], STDIN_FILENO);
		dup2(STDOUT_FILENO, pipex->pipes[WRITE_END]);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(pipex->files[READ_END]);
		close(pipex->pipes[WRITE_END]);
	}
	else
	{
		printf("redirecting file to stdout...\n");
		dup2(pipex->pipes[READ_END], STDIN_FILENO);
		dup2(STDOUT_FILENO, pipex->files[WRITE_END]);
		close(pipex->files[READ_END]);
		close(pipex->pipes[WRITE_END]);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
	}

	return 0;
}

static int	child_create(t_pipex *pipex, unsigned int cmd_index)
{
	pid_t pid;
	int runnable_index;

	pid = fork();
	if (pid == -1)
		error_exit(pipex, ERR_FORK_FAILURE);

	if (pid == 0)
	{
		printf("created child to run %s\n", pipex->cmds[cmd_index]->argv[0]);
		redirect_fd(pipex, cmd_index);
		runnable_index = cmds_get_runnable(pipex->cmds[cmd_index]);
		if (runnable_index == -1)
		{
			// TODO Handle error.
			printf("command not runnable\n");
		}
		// execve that shit
		if(execve(pipex->cmds[cmd_index]->cmd_paths[runnable_index], pipex->cmds[cmd_index]->argv, pipex->envp) == -1)
		{
			printf("execve failed with [%s]\n", strerror(errno));
			// TODO Handle error.
			error_exit(pipex, ERR_EXEC_FAILURE);
		}
		
	}
	else
	{
		int status;
		// while (wait(NULL) != -1);
		waitpid(pid, &status, WUNTRACED);
		status = WEXITSTATUS(status);
		printf("status %d\n", status);
	}


	return (0);
}

int execute_procs(t_pipex *pipex)
{
	unsigned int cmd_counter = 0;
	unsigned int cmds = cmd_count(pipex);
	// pipe(pipex->pipes);

	while (cmd_counter < cmds)
	{
		child_create(pipex, cmd_counter);
		cmd_counter++;
	}


	return (0);
}

