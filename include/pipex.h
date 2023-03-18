/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 23:11:19 by joppe         #+#    #+#                 */
/*   Updated: 2023/03/18 23:46:49 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>


// main.c
char	**split_path(char argv[]);


// utils.c
void	print_split(char **split);
int		str_arr_len(char **ptr);


// parser.c
char	**parse_args(char *argv[]);

typedef struct s_pipex
{
	char	**paths;
}	t_pipex;

#endif
