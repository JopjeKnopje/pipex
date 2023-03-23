/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 23:11:22 by joppe         #+#    #+#                 */
/*   Updated: 2023/03/23 01:40:58 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <errno.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>


int get_pipe_index(int i, int argc)
{
	if (!i)
		return (0);
	if (i == argc - 1)
	{
		return (1);
	}
	return ((i % 2) + 2);
}

// ./pipex input_file.txt "cat" "sort -n" output_file.txt
int pipex(int fd_input, int fd_output, char *argv[], char *envp[])
{
	int argc;
	t_cmd cmd_1;
	t_cmd cmd_2;

	argv = parse_args(argv);
	init_cmd(&cmd_1, argv, fd_input);
	init_cmd(&cmd_2, argv, fd_output);
	// split args and cmd
	// check with access

	

	//// Have all this stuff in a fucntion
	// pipe()
	// fork 2 times
	// dup2 (fd_input/output_file, pipe)
	// execve needs: (pathname, argv, envp)

	return 0;
}

int main(int argc, char *argv[], char *envp[])
{
	int	fd_input;
	int	fd_output;

	// TODO: Maybe use perror()
	if (argc < 5)
		return (put_str_error("Invalid number of arguments", NULL));
	if (str_is_empty(argv[2]) || str_is_empty(argv[3]))
		return (EXIT_FAILURE);

	fd_input = open(argv[1], O_RDONLY);
	fd_output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_input == -1)
		return (put_str_error(strerror(errno), argv[1]));
	if (fd_output == -1)
		return (put_str_error(strerror(errno), argv[4]));
	pipex(fd_input, fd_output, argv, envp);
	if (close(fd_input) < 0 || close(fd_output) < 0)
		return (put_str_error(strerror(errno), "fd_input"));
	return (EXIT_SUCCESS);
}
