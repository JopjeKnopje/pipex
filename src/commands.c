/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 02:01:00 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/01 16:26:57 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/unistd.h>
#include <unistd.h>

static char *find_path(char *envp[])
{
	int	i;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

// TODO Error handling / malloc protection
static char **append_env_path(t_cmd *cmd, char *path)
{
	char	**paths;
	char	*tmp;
	unsigned int i;

	if (!cmd || !path)
		return (NULL);
	
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i] && paths[i]) 
	{
		paths[i] = ft_strjoin_free(paths[i], "/");
		paths[i] = ft_strjoin_free(paths[i], cmd->argv[0]);
		i++;
	}
	paths = strjoin_free_2d(cmd->cmd_paths, paths);
	return (paths);
}

static char **append_absolute_path(t_cmd *cmd)
{
	char **prefix;

	prefix = ft_calloc(sizeof(char *), 2);
	if (!prefix)
		return (NULL);
	prefix[0] = ft_strdup("./");
	if (!prefix[0])
		return (NULL);
	prefix[0] = ft_strjoin_free(prefix[0], cmd->argv[0]);
	if (!prefix[0])
		return (NULL);
	return (prefix);
}

// TODO Exit func instead of return (NULL).
static t_cmd 	*cmd_init(char *argv, char **envp)
{
	t_cmd	*cmd;
	char	*path;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (NULL);
	cmd->argv = ft_split(argv, ' ');
	if (!cmd->argv)
	{
		free(cmd);
		return (NULL);
	}
	cmd->cmd_paths = append_absolute_path(cmd);
	if (!cmd->cmd_paths)
		return (NULL);
	path = find_path(envp);
	if (path)
		cmd->cmd_paths = append_env_path(cmd, path);
	if (!cmd->cmd_paths)
	{
		free_split(cmd->argv);
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

int 	create_commands(t_pipex *pipex, char *args[], char **envp)
{
	int 	i;
	int 	count;

	count = ft_str_arr_len(args);
	pipex->cmds = ft_calloc(sizeof(t_cmd *), count + 1);
	if (!pipex->cmds)
		error_exit(pipex, ERR_ALLOCATION_FAILURE);
	pipex->envp = envp;
	i = 0;
	while (i < count) 
	{
		pipex->cmds[i] = cmd_init(args[i], envp);
		if (!pipex->cmds[i])
		{
			free_cmds(pipex->cmds, i);
			error_exit(pipex, ERR_ALLOCATION_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

// path = strdup argument
//
// while (acces(path) == -1)
// {
// 	free path
// 	path = strjoin(argument + environment)
// 	environment ++
// }
