/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 23:11:22 by joppe         #+#    #+#                 */
/*   Updated: 2023/03/21 02:06:17 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <string.h>
#include <unistd.h>


int pipex(int argc, char *argv[], char *envp[])
{
	// TODO: Parse all the arguments
	int fd_input = open(argv[1], O_RDONLY);
	// TODO: Maybe use O_APPEND?
	int fd_output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);

	if (fd_output == -1 || fd_input == -1)
	{
		char *err = strerror(errno);
		ft_putstr_fd(err, STDERR_FILENO);
		return 1;
	}

	char **args_all = parse_args(argv);

	int fd_pipe[2];
	pipe(fd_pipe);

	if (fd_output == -1)
	{
		ft_putstr_fd("Error with fd_output\n", STDERR_FILENO);
	}

	int pid = fork();

	int exec_return = 0;
	if (pid == 0)
	{
		char **args = ft_split(args_all[1], ' ');
		close(fd_output);
		close(fd_pipe[0]);

		// Duplicate FD to FD2, closing FD2 and making it open on the same file.  
		dup2(fd_input, STDIN_FILENO);
		dup2(fd_pipe[1], STDOUT_FILENO);

		run_cmd(args, envp, args[0]);
	}
	else {
		char **args = ft_split(args_all[2], ' ');
		close(fd_input);
		close(fd_pipe[1]);

		dup2(fd_output, STDOUT_FILENO);
		dup2(fd_pipe[0], STDIN_FILENO);

		run_cmd(args, envp, args[0]);
	}
	waitpid(pid, NULL, 0);
	return 0;
}


int main(int argc, char *argv[], char *envp[])
{
	return pipex(argc, argv, envp);
}

