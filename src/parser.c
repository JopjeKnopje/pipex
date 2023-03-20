/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/18 23:44:32 by joppe         #+#    #+#                 */
/*   Updated: 2023/03/20 23:01:38 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>


char	**strjoin_free_2d(char **s_base, char **s_append)
{
	char	**s_joined;
	int		len_base;
	int		i;

	if (!s_append)
		return (NULL);
	len_base = ft_str_arr_len(s_base);
	s_joined = ft_calloc(ft_str_arr_len(s_append) + len_base + 1, sizeof(char *));
	if (!s_joined)
	{
		free(s_base);
		free(s_append);
		return NULL;
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

/*! TODO: Check how we should handle commands without arguments.
 *
 * We are currently splitting on the '"' but what if our command has no arguments?
 * aka instead of "cmd1 args" it is just literal cmd1
 */
char	**parse_args(char *argv[])
{
	char	**args_base;
	char	**split;
	int		passed;
	int		i;

	args_base = ft_calloc(1, sizeof(char *));
	if (!args_base)
		return (NULL);
	i = 1;
	while (argv[i])
	{
		split = ft_split(argv[i], '"');
		args_base = strjoin_free_2d(args_base, split);
		if (!args_base)
			break ;
		i++;
	}
	return (args_base);
}
