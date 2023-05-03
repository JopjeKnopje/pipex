/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   processes.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboeve <marvin@42.fr>                        +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/01 10:47:39 by jboeve        #+#    #+#                 */
/*   Updated: 2023/05/03 13:59:56 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_pid_t.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <unistd.h>

// Currently supports only 2 cmds
static int	redirect_fd(t_pipex *pipex, unsigned int cmd_index)
{
	// the first index
	if (!cmd_index)
	{
		// dup2(oldfd, newfd)
		dup2(pipex->files[READ_END], STDIN_FILENO);
		dup2(pipex->pipes[WRITE_END], STDOUT_FILENO);
	}
	else
	{
		dup2(pipex->files[WRITE_END], STDOUT_FILENO);
		dup2(pipex->pipes[READ_END], STDIN_FILENO);
	}
	close(pipex->files[READ_END]);
	close(pipex->files[WRITE_END]);
	close(pipex->pipes[READ_END]);
	close(pipex->pipes[WRITE_END]);

	return 0;
}

static pid_t	child_create(t_pipex *pipex, unsigned int cmd_index)
{
	pid_t pid;
	int runnable_index;

	pid = fork();
	if (pid == -1)
		error_exit(pipex, ERR_FORK_FAILURE);

	if (pid == 0)
	{
		redirect_fd(pipex, cmd_index);
		runnable_index = cmds_get_runnable(pipex->cmds[cmd_index]);
		if (runnable_index == -1)
		{
			// TODO Handle error.
			fprintf(stderr,"command not runnable\n");
			exit(0);
		}
		// if (cmd_index == 1)
		// {
		// 	char *s = "1";
		// 	s[2] = 'a';
		// }
		if(execve(pipex->cmds[cmd_index]->cmd_paths[runnable_index], pipex->cmds[cmd_index]->argv, pipex->envp) == -1)
		{
			fprintf(stderr, "execve failed with [%s]\n", strerror(errno));
			// TODO Handle error.
			error_exit(pipex, ERR_EXEC_FAILURE);
		}
	}
	return (pid);
}

int execute_procs(t_pipex *pipex)
{
	unsigned int cmd_counter = 0;
	unsigned int cmds = cmd_count(pipex);

	pid_t pid;

	while (cmd_counter < cmds)
	{
		pid = child_create(pipex, cmd_counter);
		printf("exit_status %d\n", pid);
		cmd_counter++;
	}
	close(pipex->pipes[READ_END]);
	close(pipex->pipes[WRITE_END]);

	int status;
	int exit_status;

	waitpid(pid, &status, WUNTRACED);
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		exit_status = WTERMSIG(status) + SIGNAL_OFFSET;
		printf("SIGNAL RECIEVED\n");
	}
	else if (WIFSTOPPED(status))
	{
		exit_status = WSTOPSIG(status);
	}
	return (exit_status);
}
