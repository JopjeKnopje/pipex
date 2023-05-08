/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   processes.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboeve <marvin@42.fr>                        +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/01 10:47:39 by jboeve        #+#    #+#                 */
/*   Updated: 2023/05/08 14:24:24 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	redirect_fd(t_pipex *pipex, unsigned int cmd_index)
{
	if (!cmd_index)
	{
		if (dup2(pipex->files[READ_END], STDIN_FILENO) == -1
			|| dup2(pipex->pipes[WRITE_END], STDOUT_FILENO) == -1)
			return (error_message(strerror(errno), NULL));
	}
	else
	{
		if (dup2(pipex->files[WRITE_END], STDOUT_FILENO) == -1
			|| dup2(pipex->pipes[READ_END], STDIN_FILENO) == -1)
			return (error_message(strerror(errno), NULL));
	}
	if (close(pipex->files[READ_END]) || close(pipex->files[WRITE_END])
		|| close(pipex->pipes[READ_END]) || close(pipex->pipes[WRITE_END]))
		return (error_message(strerror(errno), NULL));
	return (0);
}

static int	error_code_cmd_invalid(t_cmd *cmd)
{
	if (ft_strnstr(cmd->argv[0], "./", ft_strlen(cmd->argv[0]))
		|| cmd->argv[0][0] == '/')
	{
		error_message(error_get_name(ERR_SHELL_FILE_NOT_FOUND), cmd->argv[0]);
		return (126);
	}
	else
	{
		error_message(error_get_name(ERR_SHELL_CMD_NOT_FOUND), cmd->argv[0]);
		return (127);
	}
}

static pid_t	child_create(t_pipex *pipex, unsigned int cmd_index)
{
	int		runnable_index;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_exit(pipex, ERR_PIPEX_FORK_FAILURE);
	if (pid == 0)
	{
		if (redirect_fd(pipex, cmd_index) == EXIT_FAILURE)
			exit(EXIT_FAILURE);
		runnable_index = cmds_get_runnable(pipex->cmds[cmd_index]);
		if (runnable_index == -1)
		{
			exit(error_code_cmd_invalid(pipex->cmds[cmd_index]));
		}
		if (execve(pipex->cmds[cmd_index]->cmd_paths[runnable_index],
				pipex->cmds[cmd_index]->argv, pipex->envp) == -1)
		{
			error_exit(pipex, ERR_PIPEX_EXEC_FAILURE);
		}
	}
	return (pid);
}

static int	wait_for_children(pid_t pid)
{
	int	status;
	int	exit_status;

	waitpid(pid, &status, 0);
	while (wait(NULL) != -1)
		;
	exit_status = -1;
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_status = error_code_child_crash(status);
	return (exit_status);
}

int	execute_procs(t_pipex *pipex)
{
	unsigned int	count;
	unsigned int	i;
	pid_t			pid;

	i = 0;
	count = cmd_count(pipex);
	while (i < count)
	{
		pid = child_create(pipex, i);
		if (pid == -1)
			break ;
		i++;
	}
	if (close(pipex->pipes[READ_END]) < 0)
		return (error_message(strerror(errno), NULL));
	if (close(pipex->pipes[WRITE_END]) < 0)
		return (error_message(strerror(errno), NULL));
	return (wait_for_children(pid));
}
