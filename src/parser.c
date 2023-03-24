/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/18 23:44:32 by joppe         #+#    #+#                 */
/*   Updated: 2023/03/24 03:10:15 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>

char	**parse_args(char *argv[])
{
	char	**args_base;
	char	**split;
	int		passed;
	int		i;

	args_base = ft_calloc(1, sizeof(char *));
	if (!args_base)
		return (NULL);
	i = 2;
	while (argv[i] && argv[i + 1])
	{
		split = ft_split(argv[i], '"');
		if (!split)
		{
			free_split(args_base);
			return (NULL);
		}
		args_base = strjoin_free_2d(args_base, split);
		if (!args_base)
			break;
		i++;
	}
	return (args_base);
}

char *find_path(char *envp[])
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

char **split_path(t_cmd *cmd, char *s)
{
	char	**paths;
	char	*tmp;

	if (!cmd || !s)
		return (NULL);
	
	paths = ft_split(s, ':');

	tmp = ft_substr(paths[0], 5, ft_strlen(paths[0]) - 5);
	// TODO Error handling
	free(paths[0]);
	paths[0] = tmp;

	int i = 0;
	while (paths[i]) 
	{
		paths[i] = ft_strjoin_free(paths[i], "/");
		paths[i] = ft_strjoin_free(paths[i], cmd->argv[0]);
		i++;
	}

	// TODO: Find another way for this.
	char **arr = ft_calloc(sizeof(char *), 2);
	arr[0] = ft_strdup("./");
	arr[0] = ft_strjoin_free(arr[0], cmd->argv[0]);
	paths = strjoin_free_2d(paths, arr);
	return (paths);
}

static void error_command_not_found(char *s)
{
	write(2, "-bash: ", 7);
	write(2, s, ft_strlen(s));
	write(2, ": ", 2);
	write(2, "command not found\n", 18);
}

int		str_is_empty(char *s)
{
	int i;

	i = 0;
	while (s[i]) 
	{
		if (s[i] != ' ')
			return (0);
		i++;
	}
	error_command_not_found(s);
	return (1);
}

int	put_str_error(char *s, char *t)
{
	if (!s)
		return (2);
	if (t)
	{
		write(2, "-bash: ", 7);
		write(2, t, ft_strlen(t));
		write(2, ": ", 2);
	}
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	return (2);
}
