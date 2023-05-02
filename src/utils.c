/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/18 22:52:35 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/02 13:49:51 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <string.h>
#include <stdio.h>
#include <sys/unistd.h>
#include <unistd.h>

int cmds_get_runnable(t_cmd *cmd)
{
	int i;

 	i = 0;
	while (cmd->cmd_paths[i]) 
	{
		if (access(cmd->cmd_paths[i], X_OK))
			return (i);
		i++;
	}
	return (-1);
}

unsigned int cmd_count(t_pipex *pipex)
{
	unsigned int len;
	
	len = 0;
	while (pipex->cmds[len])
	{
		len++;
	}
	return (len);
}

char	**strjoin_free_2d(char **s_base, char **s_append)
{
	char	**s_joined;
	int		len_base;
	int		i;

	if (!s_append)
	{
		free_split(s_base);
		return (NULL);
	}
	len_base = ft_str_arr_len(s_base);
	s_joined = ft_calloc(ft_str_arr_len(s_append) + len_base + 1, sizeof(char *));
	if (!s_joined)
	{
		free_split(s_base);
		free_split(s_append);
		return (NULL);
	}
	i = 0;
	while (s_base[i])
	{
		s_joined[i] = s_base[i];
		i++;
	}
	i = 0;
	while (s_append[i])
	{
		s_joined[i + len_base] = s_append[i];
		i++;
	}
	free(s_base);
	free(s_append);
	return (s_joined);
}

