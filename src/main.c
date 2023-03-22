/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 23:11:22 by joppe         #+#    #+#                 */
/*   Updated: 2023/03/22 23:50:24 by joppe         ########   odam.nl         */
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


int pipex(int fd_input, int fd_output, char *argv[], char *envp[])
{
	char **args_all = parse_args(argv);

	int	pid1;
	int	pid2;
	int fd_pipe[2];
	pipe(fd_pipe);

	pid1 = fork();

	int exec_return = 0;
	if (pid1 == 0)
	{
		printf("child 1 lives\n");

		char **args = ft_split(args_all[1], ' ');
		close(fd_output);
		close(fd_pipe[0]);

		// Duplicate FD to FD2, closing FD2 and making it open on the same file.  
		dup2(fd_input, STDIN_FILENO);
		dup2(fd_pipe[1], STDOUT_FILENO);

		run_cmd(args, envp, args[0]);
		return 0;
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		printf("child 2 lives\n");

		char **args = ft_split(args_all[2], ' ');
		close(fd_input);
		close(fd_pipe[1]);

		dup2(fd_output, STDOUT_FILENO);
		dup2(fd_pipe[0], STDIN_FILENO);

		run_cmd(args, envp, args[0]);
		return 0;
	}
	close(fd_input);
	close(fd_output);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	free_split(args_all);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

int main(int argc, char *argv[], char *envp[])
{
	int	fd_input;
	int	fd_output;

	// TODO: Maybe use perror()
	if (argc != 5)
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
		return (put_str_error(strerror(errno), 0));
	return (EXIT_SUCCESS);
}
