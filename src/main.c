/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/27 22:06:24 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/05 16:53:53 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	pipe(pipex->pipes);
	int exit_status = execute_procs(pipex);

	// print_cmds(pipex->cmds, len);
	free_cmds(pipex->cmds);
	free_split(args);

	return (exit_status);
}

int main(int argc, char *argv[], char *envp[])
{
	t_pipex pipex;
	int exit_status;
	ft_bzero(&pipex, sizeof(pipex));

	if (argc != 5)
		(error_exit(&pipex, ERR_PIPEX_ARG_COUNT));
	if (cmd_is_empty(argv[2]) || cmd_is_empty(argv[3]))
		return (EXIT_FAILURE);
	pipex.files[READ_END] = open(argv[1], O_RDONLY);
	pipex.files[WRITE_END] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex.files[READ_END] == -1)
		return (error_message(strerror(errno), argv[1]));
	if (pipex.files[WRITE_END] == -1)
		return (error_message(strerror(errno), argv[argc - 1]));
	exit_status = do_pipex(&pipex, argv, envp);
	if (close(pipex.files[READ_END]) < 0 || close(pipex.files[WRITE_END]) < 0)
		return (error_message(strerror(errno), "pipex->fd_input"));
	return (exit_status);
}
