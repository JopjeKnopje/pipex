/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboeve <marvin@42.fr>                        +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/19 16:10:36 by jboeve        #+#    #+#                 */
/*   Updated: 2023/04/19 17:45:13 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


// TODO Free stuff from pipex struct
void error_exit(t_pipex *pipex, t_error err)
{
	const char *ERR_NAMES[] = {
		"Malloc failure\n",
	};

	write(STDERR_FILENO, ERR_NAMES[err], ft_strlen(ERR_NAMES[err]));
	exit(EXIT_FAILURE);
}
