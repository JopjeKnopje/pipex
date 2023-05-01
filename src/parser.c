/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/18 23:44:32 by joppe         #+#    #+#                 */
/*   Updated: 2023/04/19 17:33:25 by jboeve        ########   odam.nl         */
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
		// TODO Handle strjoin_free_2d fail.
		args_base = strjoin_free_2d(args_base, split);
		if (!args_base)
			break;
		i++;
	}
	return (args_base);
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
