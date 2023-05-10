/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/27 22:06:24 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/10 08:36:55 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

static int	do_pipex(t_pipex *pipex, char *argv[], char *envp[])
{
	char	**args;
	int		exit_status;

	exit_status = EXIT_FAILURE;
	args = parse_args(argv);
	if (!args)
		return (exit_status);
	if (create_commands(pipex, args, envp) != EXIT_SUCCESS)
	{
		free_split(args);
		error_message(error_get_name(ERR_PIPEX_ALLOCATION_FAILURE), NULL);
		return (exit_status);
	}
	free_split(args);
	if (pipe(pipex->pipes) == -1)
	{
		error_message(strerror(errno), NULL);
		free_cmds(pipex->cmds);
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
		(error_exit(&pipex, ERR_PIPEX_ARG_COUNT));
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
