/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                            :+:    :+:             */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 00:15:01 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/15 10:59:58 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_cmd(t_cmd *cmd)
{
	free_split(cmd->argv);
	free_split(cmd->cmd_paths);
	free(cmd);
}

void	free_cmds(t_cmd **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		free_cmd(cmds[i]);
		i++;
	}
	free(cmds);
}

void	free_split(char **s_split)
{
	int	i;

	i = 0;
	while (s_split[i])
	{
		free(s_split[i]);
		i++;
	}
	free(s_split);
}

void	free_split_skip(char **s_split, int skip)
{
	int	i;

	i = 0;
	while (s_split[i] || i <= skip)
	{
		if (i != skip)
			free(s_split[i]);
		i++;
	}
	free(s_split);
}
