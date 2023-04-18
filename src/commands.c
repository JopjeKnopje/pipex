/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 02:01:00 by joppe         #+#    #+#                 */
/*   Updated: 2023/04/18 20:55:14 by joppe         ########   odam.nl         */
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
			return (envp[i]);
		i++;
	}
	return (NULL);
}

// TODO Error handling / malloc protection
static char **append_env_path(t_cmd *cmd, char *path)
{
	char	**paths;
	char	*tmp;

	if (!cmd || !path)
		return (NULL);
	
	paths = ft_split(path, ':');

	tmp = ft_substr(paths[0], 5, ft_strlen(paths[0]) - 5);
	free(paths[0]);
	paths[0] = tmp;

	int i = 0;
	while (paths[i]) 
	{
		// tmp is the path with the command
		paths[i] = ft_strjoin_free(paths[i], "/");
		paths[i] = ft_strjoin_free(paths[i], cmd->argv[0]);
		// // access(cmds[i]->cmd_paths[j], X_OK) == -1
		// if (access(tmp, X_OK) == 0)
		// {
		// 	printf("added [%s] to paths\n", tmp);
		// 	paths[i] = tmp;
		// }
		i++;
	}

	// TODO: Find another way for this.
	char **arr = ft_calloc(sizeof(char *), 2);
	arr[0] = ft_strdup("./");
	arr[0] = ft_strjoin_free(arr[0], cmd->argv[0]);
	paths = strjoin_free_2d(paths, arr);
	return (paths);
}

static char *append_abolute_path(t_cmd *cmd)
{

}

static t_cmd 	*cmd_init(char *argv, char **envp)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (NULL);
	cmd->argv = ft_split(argv, ' ');
	if (!cmd->argv)
	{
		free(cmd);
		return (NULL);
	}
	char *path = find_path(envp);
	if (path)
	{
		cmd->cmd_paths = append_env_path(cmd, path);
	}
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
