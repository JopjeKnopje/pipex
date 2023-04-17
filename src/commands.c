/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 02:01:00 by joppe         #+#    #+#                 */
/*   Updated: 2023/04/17 14:48:54 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd 	*cmd_init(char *argv, char **envp)
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
	cmd->cmd_paths = split_path(cmd, find_path(envp));
	if (!cmd->cmd_paths)
	{
		free_split(cmd->argv);
		free(cmd);
		return (NULL);
	}
	return (cmd);
}
