/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/18 22:52:35 by joppe         #+#    #+#                 */
/*   Updated: 2023/03/27 22:04:52 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int check_exec(t_cmd **cmds, int len)
{
	int	i;
	int	j;
	int err;

	i = 0;
	while (i < len)
	{
		j = 0;
		err = 0;
		while (cmds[i]->cmd_paths[j]) 
		{
			// TODO: Only return 1 when we can atleast run one of each command
			if (access(cmds[i]->cmd_paths[j], X_OK) == -1)
			{
				err = 1;
			}
			j++;
		}
		if (err == 1)
		{
			if (errno == 2)
				put_str_error("command not found", cmds[i]->argv[0]);
			else
				put_str_error(strerror(errno), cmds[i]->argv[0]);
			return (1);
		}
		i++;
	}
	return (0);
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

