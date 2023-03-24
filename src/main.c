/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 23:11:22 by joppe         #+#    #+#                 */
/* 	 Updated: 2023/03/23 23:53:30 by joppe         ########   odam.nl         */
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

void struct_print_cmd(t_cmd *cmd)
{
	char *argv = sprint_split(cmd->argv, "cmd->argv");
	char *paths = sprint_split(cmd->cmd_paths, "cmd->cmd_paths");
	printf("argv [%s] | paths [%s]\n", argv, paths);
	free(argv);
	free(paths);
}

t_cmd *create_commands(char *s_args[], int count, char **envp)
{
	t_cmd *cmd;



	cmd = cmd_init(s_args[0], envp);


	int i = 0;
	printf("cmds[%d]->argv[0]: [%s]\n", i, cmd->argv[0]);
	printf("cmds[%d]->cmd_paths[0]: [%s]\n", i, cmd->cmd_paths[0]);

	return (cmd);
}

// ./pipex input_file.txt "cat" "sort -n" output_file.txt
int pipex(int fd_input, int fd_output, char *argv[], char *envp[])
{
	char **args;

	args = parse_args(argv);

	int count = ft_str_arr_len(args);
	t_cmd *cmd = create_commands(args, count, envp);



	free_split(cmd->argv);
	free_split(cmd->cmd_paths);
	free(cmd);

	free_split(args);



	
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
