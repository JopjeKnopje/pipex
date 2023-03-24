/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 02:01:00 by joppe         #+#    #+#                 */
/*   Updated: 2023/03/24 01:23:06 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>

// First try the approach with all the handling in here.
t_cmd 	*cmd_init(char *argv, char **envp)
{
	t_cmd *cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (NULL);
	cmd->argv = ft_split(argv, ' ');
	if (!cmd->argv)
		return (NULL);
	cmd->cmd_paths = split_path(cmd, find_path(envp));
	if (!cmd->cmd_paths)
		return (NULL);
	return (cmd);
}


int run_cmd(char *argv[], char *envp[], char *cmd)
{
	int i;
	int ret;
	char *path;
	char **paths;

	path = find_path(envp);
	paths = split_path(NULL, path);

	i = 1;
	while (paths[i]) 
	{
		paths[i] = ft_strjoin_free(paths[i], cmd);
		ret = execve(paths[i], argv, envp);
		i++;
	}
	if (ret == -1)
	{
		ft_putstr_fd("error cant start process\n", STDERR_FILENO);
	}
	free_split(paths);
	return 0;
}

