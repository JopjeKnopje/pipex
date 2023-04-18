/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/27 22:06:24 by joppe         #+#    #+#                 */
/*   Updated: 2023/04/18 20:51:26 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int pipex(int fd_input, int fd_output, char *argv[], char *envp[])
{
	char **args;

	args = parse_args(argv);
	if (!args)
		return (EXIT_FAILURE);
	int len = ft_str_arr_len(args);
	t_cmd **cmds = create_commands(args, len, envp);
	if (!cmds)
	{
		printf("cmds failed\n");
		free_split(args);
		return (EXIT_FAILURE);
	}

	print_cmds(cmds, len);


	free_cmds(cmds, len);
	free_split(args);


	// Have all this stuff in a fucntion
	// pipe()
	// fork 2 times
	// dup2 (fd_input/output_file, pipe)
	// execve needs: (pathname, argv, envp)

	return 0;
}

// TODO: Reformat main so it accepts unlimited arguments
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
	fd_output = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_input == -1)
		return (put_str_error(strerror(errno), argv[1]));
	if (fd_output == -1)
		return (put_str_error(strerror(errno), argv[argc - 1]));
	pipex(fd_input, fd_output, argv, envp);
	if (close(fd_input) < 0 || close(fd_output) < 0)
		return (put_str_error(strerror(errno), "fd_input"));
	return (EXIT_SUCCESS);
}
