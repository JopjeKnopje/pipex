/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboeve <marvin@42.fr>                        +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/19 16:10:36 by jboeve        #+#    #+#                 */
/*   Updated: 2023/05/05 02:16:32 by joppe         ########   odam.nl         */
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



static void error_command_not_found(char *s)
{
	write(2, "-bash: ", 7);
	write(2, s, ft_strlen(s));
	write(2, ": ", 2);
	write(2, "command not found\n", 18);
}

int		str_is_empty(char *s)
{
	int i;

	if (!s)
		return (1);
	i = 0;
	while (s[i]) 
	{
		if (s[i] != ' ')
			return (0);
		i++;
	}
	error_command_not_found(s);
	return (1);
}

int	put_str_error(char *s, char *t)
{
	if (!s)
		return (2);
	if (t)
	{
		write(2, "-bash: ", 7);
		write(2, t, ft_strlen(t));
		write(2, ": ", 2);
	}
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	return (2);
}
