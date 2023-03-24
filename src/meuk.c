/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   meuk.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 01:45:35 by joppe         #+#    #+#                 */
/*   Updated: 2023/03/24 02:40:49 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void print_cmds(t_cmd **cmds, int len)
{
	int i = 0;
	while (i < len) 
	{
		char *argv = sprint_split(cmds[i]->argv, NULL);
		char *paths = sprint_split(cmds[i]->cmd_paths, NULL);
		printf("cmds[%d]->argv[0]: [%s]\n", i, argv);
		printf("cmds[%d]->cmd_paths[0]: [%s]\n", i, paths);
		free(argv);
		free(paths);
		i++;
	}
}


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
	len = 0;
	if (name)
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

	if (name)
	{
		ft_strlcat(s, name, size);
		ft_strlcat(s, ": ", size);
	}

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

