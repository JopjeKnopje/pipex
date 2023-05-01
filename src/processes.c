/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   processes.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboeve <marvin@42.fr>                        +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/01 10:47:39 by jboeve        #+#    #+#                 */
/*   Updated: 2023/05/01 15:54:46 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static int	child_create(t_pipex *pipex, unsigned int proc_counter)
{
	pid_t pid;
	unsigned int i;
	unsigned int j;

	i = 0;
	pid = fork();
	if (pid == -1)
		error_exit(pipex, ERR_FORK_FAILURE);

	if (pid == 0)
	{
		while (pipex->cmds[proc_counter]->cmd_paths[i])
		{
			// TODO Check access
			if (access(pipex->cmds[proc_counter]->cmd_paths[i], X_OK) == -1)
			{
				printf("access failed %s\n", pipex->cmds[proc_counter]->argv[0]);
			}
			else
				execve(pipex->cmds[proc_counter]->cmd_paths[i], pipex->cmds[proc_counter]->argv, pipex->envp);
			i++;
		}
		printf("could not find executable %s\n", pipex->cmds[proc_counter]->argv[0]);
		exit(0);
	}
	else
	{
		// parent
	}


	return (0);
}

int execute_procs(t_pipex *pipex)
{
	unsigned int proc_counter = 0;
	unsigned int cmds = cmd_count(pipex);
	// pipe(pipex->pipes);

	while (proc_counter < cmds)
	{
		child_create(pipex, proc_counter);
		proc_counter++;
	}


	return (0);
}
