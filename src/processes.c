/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   processes.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboeve <marvin@42.fr>                        +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/01 10:47:39 by jboeve        #+#    #+#                 */
/*   Updated: 2023/05/02 15:20:08 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

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

