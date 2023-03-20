/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 23:11:19 by joppe         #+#    #+#                 */
/*   Updated: 2023/03/20 23:01:20 by joppe         ########   odam.nl         */
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


// parser.c
char	**parse_args(char *argv[]);

#endif
