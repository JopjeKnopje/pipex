/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboeve <marvin@42.fr>                        +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/19 16:10:36 by jboeve        #+#    #+#                 */
/*   Updated: 2023/05/05 01:39:50 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	const char *ERR_NAMES[] = {
		"Malloc failure\n",
		"Fork failure\n",
	};


	write(STDERR_FILENO, ERR_NAMES[err], ft_strlen(ERR_NAMES[err]));
	exit(EXIT_FAILURE);
}

