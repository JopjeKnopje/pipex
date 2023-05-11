/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                          :+:    :+:             */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/18 23:44:32 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/11 11:53:46 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
			break ;
		i++;
	}
	return (args_base);
}

int	cmds_is_empty(char **argv, int count)
{
	int	i;

	i = 2;
	while (i < count)
	{
		if (ft_strisempty(argv[i]))
		{
			error_message(error_get_name(ERR_SHELL_CMD_NOT_FOUND), argv[i]);
			return (i);
		}
		i++;
	}
	return (0);
}
