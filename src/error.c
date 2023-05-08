/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboeve <marvin@42.fr>                        +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/19 16:10:36 by jboeve        #+#    #+#                 */
/*   Updated: 2023/05/08 12:07:46 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int error_code_child_crash(int status)
{
	int signal_status = WTERMSIG(status);
	ft_putstr_fd(strsignal(signal_status), STDERR_FILENO);
	if (WCOREDUMP(status))
	{
		ft_putstr_fd(" (core dumped)", STDERR_FILENO);
	}
	ft_putendl_fd("", STDERR_FILENO);
	return (signal_status + SIGNAL_OFFSET);
}

const char *error_get_name(t_error err)
{
	static const char *ERR_NAMES[] = {
		"Malloc failure",
		"Fork failure",
		"Exec failure",
		"Usage: pipex input_file \"cmd1 args\" \"cmd2 args\" output_file",
		"command not found",
		"No such file or directory",
	};

	return ERR_NAMES[err];
}

void error_exit(t_pipex *pipex, t_error err)
{
	error_message(error_get_name(err), NULL);
	if (err == ERR_PIPEX_EXEC_FAILURE || err == ERR_PIPEX_FORK_FAILURE)
	{
		free_cmds(pipex->cmds);
	}
	exit(EXIT_FAILURE);
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

