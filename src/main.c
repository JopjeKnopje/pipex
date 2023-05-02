/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/27 22:06:24 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/02 11:34:28 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>


static int do_pipex(t_pipex *pipex, char *argv[], char *envp[])
{
	char **args;

	args = parse_args(argv);
	if (!args)
		return (EXIT_FAILURE);
	if (create_commands(pipex, args, envp) != EXIT_SUCCESS)
	{
		printf("cmds failed\n");
		free_split(args);
		return (EXIT_FAILURE);
	}

	// pipe(pipex->pipes);


	// execute_procs(pipex);
	// execve(pipex->cmds[0]->cmd_paths[0], pipex->cmds[0]->argv, pipex->envp);


	int len = ft_str_arr_len(args);
	print_cmds(pipex->cmds, len);
	free_cmds(pipex->cmds, len);
	free_split(args);

	// Have all this stuff in a fucntion
	// pipe()
	// fork 2 times
	// dup2 (fd_input/output_file, pipe)
	// execve needs: (pathname, argv, envp)

	return (EXIT_SUCCESS);
}

void leaks()
{
	// system("leaks -q pipex");
}

int main(int argc, char *argv[], char *envp[])
{
	t_pipex pipex;
	ft_bzero(&pipex, sizeof(pipex));

	// TODO: Maybe use perror()
	// if (argc != 5)
	// if (argc < 5)
	// 	return (put_str_error("Invalid number of arguments", NULL));
	if (str_is_empty(argv[2]) || str_is_empty(argv[3]))
		return (EXIT_FAILURE);
	pipex.files[READ_END] = open(argv[1], O_RDONLY);
	pipex.files[WRITE_END] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex.files[READ_END] == -1)
		return (put_str_error(strerror(errno), argv[1]));
	if (pipex.files[WRITE_END] == -1)
		return (put_str_error(strerror(errno), argv[argc - 1]));
	do_pipex(&pipex, argv, envp);
	if (close(pipex.files[READ_END]) < 0 || close(pipex.files[WRITE_END]) < 0)
		return (put_str_error(strerror(errno), "pipex->fd_input"));
	leaks();
	printf("\n\n");
	return (EXIT_SUCCESS);
}

