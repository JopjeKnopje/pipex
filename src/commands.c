/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 02:01:00 by joppe         #+#    #+#                 */
/*   Updated: 2023/04/19 11:49:53 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdio.h>
#include <unistd.h>

static char *find_path(char *envp[])
{
	int i = 0;
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
	int		i;

	if (!cmd || !path)
		return (NULL);
	
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i]) 
	{
		paths[i] = ft_strjoin_free(paths[i], "/");
		paths[i] = ft_strjoin_free(paths[i], cmd->argv[0]);
		// TODO Check access
		// if (access(tmp, X_OK) == 0)
		// {
		// 	printf("added [%s] to paths\n", tmp);
		// 	paths[i] = tmp;
		// }
		i++;
	}
	paths = strjoin_free_2d(cmd->cmd_paths, paths);
	return (paths);
}

static char **append_abolute_path(t_cmd *cmd)
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
	cmd->cmd_paths = append_abolute_path(cmd);
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

t_cmd **create_commands(char *args[], int count, char **envp)
{
	t_cmd **cmds;
	
	cmds = ft_calloc(sizeof(t_cmd *), count);
	if (!cmds)
		return (NULL);
	int i = 0;
	while (i < count) 
	{
		cmds[i] = cmd_init(args[i], envp);
		// TODO Check access.
		if (!cmds[i])
		{
			free_cmds(cmds, i);
			return (NULL);
		}
		i++;
	}
	return (cmds);
}
