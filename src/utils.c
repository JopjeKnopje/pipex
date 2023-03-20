/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/18 22:52:35 by joppe         #+#    #+#                 */
/*   Updated: 2023/03/20 23:00:13 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
