/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 23:11:19 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/02 10:50:03 by jboeve        ########   odam.nl         */
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

#define READ_END 0
#define WRITE_END 1

typedef struct s_cmd
{
	char **argv;    	// the argv with the program name ["cat -e", "e", "test_file.txt"]
	char **cmd_paths; 	// the command with the appended path
}	t_cmd;

typedef struct s_pipex
{
	int 	files[2];
	int 	pipes[2];
	t_cmd	**cmds;
	char	**envp;

}	t_pipex;

typedef enum e_error
{
	ERR_ALLOCATION_FAILURE,
	ERR_FORK_FAILURE,
	ERR_SHELL_CMD_NOT_FOUND,
	ERR_SHELL_FILE_NOT_FOUND,
}	t_error;



// processes.c
int execute_procs(t_pipex *pipex);


// free.c
void 	free_cmd(t_cmd *cmd);
void 	free_cmds(t_cmd **cmds, unsigned int len);
void	free_split(char **s_split);


// utils.c
char	**strjoin_free_2d(char **s_base, char **s_append);
unsigned int cmd_count(t_pipex *pipex);


// parser.c
char	**parse_args(char *argv[]);
int		str_is_empty(char *s);
int		put_str_error(char *s, char *t);


// commands.c
int 	create_commands(t_pipex *pipex, char *args[], char **envp);

// error.c
void 	error_exit(t_pipex *pipex, t_error err);

// meuk.c
void	print_split(char **split);
void 	print_cmds(t_cmd **cmds, int len);
char 	*sprint_split(char **split, const char *name);

#endif
