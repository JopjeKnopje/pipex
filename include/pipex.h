/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 23:11:19 by joppe         #+#    #+#                 */
/*   Updated: 2023/03/23 01:40:31 by joppe         ########   odam.nl         */
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

typedef struct s_cmd
{
	int fd_input;  // whatever stdin is
	int fd_output; // whatever stdout is
	char **argv;    // the argv with the program name ["cat", "e", "test_file.txt"]
	char *cmd; 		// the command with path
}	t_cmd;


// utils.c
void	print_split(char **split);
char 	*sprint_split(char **split, const char *name);
void	free_split(char **s_split);
char	**strjoin_free_2d(char **s_base, char **s_append);
t_cmd 	*init_cmd(t_cmd *cmd, char *argv[], int fd_input);


// parser.c
char	**parse_args(char *argv[]);
char 	*find_path(char *envp[]);
char 	**split_path(char *s);
int		str_is_empty(char *s);
int		put_str_error(char *s, char *t);


// commands.c
int 	run_cmd(char *argv[], char *envp[], char *cmd);

#endif
