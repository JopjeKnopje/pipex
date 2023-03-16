/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 23:11:22 by joppe         #+#    #+#                 */
/*   Updated: 2023/03/16 23:55:41 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "pipex.h"
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd[2];
	if (pipe(fd) == -1)
	{
		printf("error creating pipe\n");
		return 1;
	}


	int id = fork();
	if (id == -1)
	{
		printf("error forking\n");
		return 1;
	}

	if (id == 0)
	{
		printf("created child with fd %d\n", id);
		ft_putstr_fd("input a string: ", 0);

		char *line = get_next_line(STDIN_FILENO);
		write(fd[1], line, ft_strlen(line));
		close(fd[1]);
		close(fd[0]);
	}
	else
	{
		close(fd[1]);
		printf("created parent with fd %d\n", id);
		char *line = get_next_line(fd[0]);
		close(fd[0]);
		printf("data from pipe [%s]\n", line);
	}

	return (0);
}
