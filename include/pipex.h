/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 23:11:19 by joppe         #+#    #+#                 */
/*   Updated: 2023/03/21 02:02:40 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>


// utils.c
void	print_split(char **split);
char 	*sprint_split(char **split, const char *name);
void	free_split(char **s_split);
char	**strjoin_free_2d(char **s_base, char **s_append);


// parser.c
char	**parse_args(char *argv[]);
char 	*find_path(char *envp[]);
char 	**split_path(char *s);

// commands.c
int 	run_cmd(char *argv[], char *envp[], char *cmd);

#endif
