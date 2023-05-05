/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboeve <marvin@42.fr>                        +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/19 16:10:36 by jboeve        #+#    #+#                 */
/*   Updated: 2023/05/05 17:12:07 by joppe         ########   odam.nl         */
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

// TODO Free stuff from pipex struct
void error_exit(t_pipex *pipex, t_error err)
{
	write(STDERR_FILENO, ERR_NAMES[err], ft_strlen(ERR_NAMES[err]));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

int	error_message(char *s, char *cmd)
{
	if (!s)
		return (2);
	if (cmd)
	{
		write(STDERR_FILENO, "-bash: ", 7);
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": ", 2);
	}
	write(STDERR_FILENO, s, ft_strlen(s));
	write(STDERR_FILENO, "\n", 1);
	return (EXIT_FAILURE);
}

