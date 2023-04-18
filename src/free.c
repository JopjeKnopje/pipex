/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 00:15:01 by joppe         #+#    #+#                 */
/*   Updated: 2023/04/18 20:03:04 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


void	free_cmds(t_cmd **cmds, unsigned int len)
{
	int	i;
	
	i = 0;
	while (i < len)
	{
		free_split(cmds[i]->argv);
		free_split(cmds[i]->cmd_paths);
		free(cmds[i]);
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

