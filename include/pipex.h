/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 23:11:19 by joppe         #+#    #+#                 */
/*   Updated: 2023/04/19 10:53:38 by jboeve        ########   odam.nl         */
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
#include <string.h>
#include <sys/wait.h>

typedef struct s_cmd
{
	char **argv;    	// the argv with the program name ["cat -e", "e", "test_file.txt"]
	char **cmd_paths; 	// the command with the appended path
}	t_cmd;


// free.c
void 	free_cmds(t_cmd **cmds, unsigned int len);
void	free_split(char **s_split);


// utils.c
char	**strjoin_free_2d(char **s_base, char **s_append);


// parser.c
char	**parse_args(char *argv[]);
int		str_is_empty(char *s);
int		put_str_error(char *s, char *t);


// commands.c
t_cmd	**create_commands(char *s_args[], int count, char **envp);


// meuk.c
void	print_split(char **split);
void 	print_cmds(t_cmd **cmds, int len);
char 	*sprint_split(char **split, const char *name);

#endif
