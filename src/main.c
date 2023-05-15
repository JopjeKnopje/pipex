/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/10 15:26:15 by jboeve        #+#    #+#                 */
/*   Updated: 2023/05/15 16:10:31 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdio.h>

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
	// print_cmds(pipex->cmds, 2);
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
	pipex.fnames[READ_END] = argv[1];
	pipex.fnames[WRITE_END] = argv[argc - 1];
	exit_status = do_pipex(&pipex, argv, envp);
	return (exit_status);
}
