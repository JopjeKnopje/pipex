/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                             :+:    :+:            */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/10 15:26:15 by jboeve        #+#    #+#                 */
/*   Updated: 2023/05/15 09:38:23 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>

static int	do_pipex(t_pipex *pipex, char *argv[], char *envp[])
{
	char	**args;
	int		exit_status;

	args = parse_args(argv);
	if (!args)
		return (EXIT_FAILURE);
	if (!create_commands(pipex, args, envp))
	{
		error_message(error_get_name(ERR_PIPEX_ALLOCATION_FAILURE), NULL);
		free_split(args);
		return (EXIT_FAILURE);
	}
	free_split(args);
	if (pipe(pipex->pipes) == -1)
	{
		error_message(strerror(errno), NULL);
		free_cmds(pipex->cmds);
		return (EXIT_FAILURE);
	}
	exit_status = execute_procs(pipex);
	free_cmds(pipex->cmds);
	return (exit_status);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	int		exit_status;

	if (argc != 5)
		error_exit(&pipex, ERR_PIPEX_ARG_COUNT);
	if (cmds_is_empty(argv, argc - 1))
		return (127);
	pipex.files[READ_END] = open(argv[1], O_RDONLY);
	pipex.files[WRITE_END] = open(argv[argc - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex.files[READ_END] == -1)
		return (error_message(strerror(errno), argv[1]));
	if (pipex.files[WRITE_END] == -1)
		return (error_message(strerror(errno), argv[argc - 1]));
	exit_status = do_pipex(&pipex, argv, envp);
	if (close(pipex.files[READ_END]) < 0)
		return (error_message(strerror(errno), argv[1]));
	if (close(pipex.files[WRITE_END]) < 0)
		return (error_message(strerror(errno), argv[argc - 1]));
	return (exit_status);
}

static void print_paths(char **paths, unsigned int len)
{
	unsigned int i = 0;
	while (i < len) 
	{
		printf("paths[%d]: %s\n", i, paths[i]);
		i++;
	}
}

int main1(int argc, char *argv[])
{
	const char *s = "/home/joppe/.cargo/bin:/home/joppe/gems/bin:/home/joppe/.local/bin";
	char **paths = ft_split(s, ':');

	print_paths(paths, 4);

	free(paths[1]);
	paths[1] = NULL;
	print_paths(paths, 4);

	free_split_test(paths, 1);

	return EXIT_SUCCESS;
}
