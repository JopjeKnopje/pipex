/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 02:01:00 by joppe         #+#    #+#                 */
/*   Updated: 2023/03/21 02:02:25 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int run_cmd(char *argv[], char *envp[], char *cmd)
{
	int i;
	int ret;
	char *path;
	char **paths;

	path = find_path(envp);
	paths = split_path(path);

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

