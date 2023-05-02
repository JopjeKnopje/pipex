/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   processes.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboeve <marvin@42.fr>                        +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/01 10:47:39 by jboeve        #+#    #+#                 */
/*   Updated: 2023/05/02 13:45:08 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static int	child_create(t_pipex *pipex, unsigned int cmd_index)
{
	pid_t pid;
	t_cmd *runnable_cmd;

	pid = fork();
	if (pid == -1)
		error_exit(pipex, ERR_FORK_FAILURE);

	if (pid == 0)
	{
		// check with access if we can run the file/command, return said command.
		runnable_cmd = cmds_get_runnable(pipex->cmds[cmd_index]);
		// execve that shit
	}
	else
	{
		// parent
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
