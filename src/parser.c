/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/18 23:44:32 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/05 17:58:40 by joppe         ########   odam.nl         */
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

int		str_is_empty(char *s)
{
	int i;

	i = 0;
	if (!s)
		return (1);
	while (s[i]) 
	{
		if (s[i] != ' ')
			return (0);
		i++;
	}
	error_message((char *) ERR_NAMES[ERR_SHELL_CMD_NOT_FOUND], s);
	exit(127);
}
