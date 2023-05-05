/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 00:15:01 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/05 02:09:22 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


void 	free_cmd(t_cmd *cmd)
{
	free_split(cmd->argv);
	free_split(cmd->cmd_paths);
	free(cmd);
}


// TODO Find cmds len.
void	free_cmds(t_cmd **cmds)
{
	int	i;
	
	i = 0;
	// while (i < len)
	while (cmds[i])
	{
		free_cmd(cmds[i]);
		i++;
	}
	free(cmds);
}
  
// Free a string array.
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

