/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/18 22:52:35 by joppe         #+#    #+#                 */
/*   Updated: 2023/03/23 01:37:24 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdio.h>

void print_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		printf("split[%d] [%s]\n", i, split[i]);
		i++;
	}
}

char *sprint_split(char **split, const char *name)
{
	int i;
	int len;
	const char *delim = ", ";

	i = 0;
	len = ft_strlen(name) + 2;
	while (split[i])
	{
		len += ft_strlen(split[i]);
		i++;
		if (split[i])
			len += ft_strlen(delim);
	}
	int size = (len) + 1 * sizeof(char);
	char *s = ft_calloc(size, 1);

	ft_strlcat(s, name, size);
	ft_strlcat(s, ": ", size);

	i = 0;
	while (split[i])
	{
		ft_strlcat(s, split[i], size);
		int j = 0;
		i++;
		if (split[i])
			ft_strlcat(s, delim, size);
	}
	return s;
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

t_cmd 	*init_cmd(t_cmd *cmd, char *argv[], int fd_input)
{
	cmd->argv = argv;
	cmd->fd_input = fd_input;

	return (cmd);
}
