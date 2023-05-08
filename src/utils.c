/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/18 22:52:35 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/08 13:59:08 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	char	**free_ptr2(char **p1, char **p2)
{
	free(p1);
	free(p2);
	return (NULL);
}

int	cmds_get_runnable(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd_paths[i])
	{
		if (access(cmd->cmd_paths[i], X_OK) == 0)
			return (i);
		i++;
	}
	return (-1);
}

unsigned	int	cmd_count(t_pipex *pipex)
{
	unsigned int	len;

	len = 0;
	while (pipex->cmds[len])
		len++;
	return (len);
}

char	**strjoin_free_2d(char **s_base, char **s_append)
{
	char	**s_joined;
	int		len;
	int		i;

	if (!s_append)
		return (NULL);
	len = ft_str_arr_len(s_base);
	s_joined = ft_calloc(ft_str_arr_len(s_append) + len + 1, sizeof(char *));
	if (!s_joined)
		return (free_split(s_base), free_split(s_append), NULL);
	i = 0;
	while (s_base[i])
	{
		s_joined[i] = s_base[i];
		i++;
	}
	i = 0;
	while (s_append[i])
	{
		s_joined[i + len] = s_append[i];
		i++;
	}
	free_ptr2(s_base, s_append);
	return (s_joined);
}
