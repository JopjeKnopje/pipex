/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                           :+:    :+:             */
/*                                                     +:+                    */
/*   By: jboeve <marvin@42.fr>                        +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/19 16:10:36 by jboeve        #+#    #+#                 */
/*   Updated: 2023/05/15 14:39:04 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>

int	error_code_child_crash(int status)
{
	int	signal_status;

	signal_status = WTERMSIG(status);
	if (WCOREDUMP(status))
		ft_putstr_fd(" (core dumped)", STDERR_FILENO);
	ft_putendl_fd("", STDERR_FILENO);
	return (signal_status + SIGNAL_OFFSET);
}

const	char	*error_get_name(t_error err)
{
	static const char	*err_names[] = {
		"Malloc failure",
		"Fork failure",
		"Exec failure",
		"Usage: pipex input_file \"cmd1 args\" \"cmd2 args\" output_file",
		"command not found",
		"No such file or directory",
	};

	return (err_names[err]);
}

void	error_exit(t_pipex *pipex, t_error err)
{
	error_message(error_get_name(err), NULL);
	if (err == ERR_PIPEX_EXEC_FAILURE || err == ERR_PIPEX_FORK_FAILURE)
		free_cmds(pipex->cmds);
	exit(EXIT_FAILURE);
}

int	error_message_errno(char *cmd)
{
	error_message(strerror(errno), cmd);
	if (errno == 2 || errno == 13)
		return (0);
	return (1);
}

int	error_message(const char *s, char *cmd)
{
	if (!s)
		return (2);
	if (cmd)
	{
		write(STDERR_FILENO, "bash: ", 7);
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": ", 2);
	}
	write(STDERR_FILENO, s, ft_strlen(s));
	write(STDERR_FILENO, "\n", 1);
	return (EXIT_FAILURE);
}
