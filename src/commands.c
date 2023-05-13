/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   commands.c                                         :+:    :+:            */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/10 15:25:47 by jboeve        #+#    #+#                 */
/*   Updated: 2023/05/13 10:53:53 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>

char	*find_path(char *envp[])
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

static char	**append_path_env(t_cmd *cmd, char *path)
{
	unsigned int	i;
	char			**paths;

	static int counter = 0;

	if (!cmd || !path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		// TODO Fix these leaks
		if (counter)
			paths[i] = NULL;
		else
			paths[i] = ft_strjoin_free(paths[i], "/");
		counter++;
		if (!paths[i])
		{
			free_split(paths);
			return (NULL);
		}
		paths[i] = ft_strjoin_free(paths[i], cmd->argv[0]);
		if (!paths[i])
			return (NULL);
		i++;
	}
	return (paths);
}

static int	append_path_file(t_cmd *cmd)
{
	cmd->cmd_paths = ft_calloc(sizeof(char *), 2);
	if (!cmd->cmd_paths)
	{
		free(cmd);
		return (0);
	}
	cmd->cmd_paths[0] = ft_strdup(cmd->argv[0]);
	if (!cmd->cmd_paths[0])
	{
		free_cmd(cmd);
		return (0);
	}
	return (1);
}

static t_cmd	*cmd_init(char *argv, char **envp)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (NULL);
	cmd->argv = ft_split(argv, ' ');
	if (!cmd->argv)
		return (free(cmd), NULL);
	if (ft_strnstr(cmd->argv[0], "/", ft_strlen(cmd->argv[0]))
		|| !find_path(envp))
	{
		if (!append_path_file(cmd))
			return (NULL);
	}
	else
	{
		// TODO Check leaks
		cmd->cmd_paths = append_path_env(cmd, find_path(envp));
		if (!cmd->cmd_paths)
		{
			printf("append_path_env failed\n");
			free_split(cmd->argv);
			free(cmd);
			return (NULL);
		}
	}
	return (cmd);
}

int	create_commands(t_pipex *pipex, char *args[], char **envp)
{
	unsigned int	i;
	unsigned int	count;

	count = ft_str_arr_len(args);
	pipex->cmds = ft_calloc(sizeof(t_cmd *), count + 1);
	if (!pipex->cmds)
		return (0);
	pipex->envp = envp;
	i = 0;
	while (i < count)
	{
		pipex->cmds[i] = cmd_init(args[i], envp);
		if (!pipex->cmds[i])
		{
			free_cmds(pipex->cmds);
			return (0);
		}
		i++;
	}
	return (1);
}
