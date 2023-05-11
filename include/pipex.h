/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                           :+:    :+:             */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 23:11:19 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/11 13:46:58 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>

# define READ_END 0
# define WRITE_END 1
# define SIGNAL_OFFSET 128

typedef struct s_cmd
{
	char	**argv;
	char	**cmd_paths;
}	t_cmd;

typedef struct s_pipex
{
	int		files[2];
	int		pipes[2];
	t_cmd	**cmds;
	char	**envp;
}	t_pipex;

typedef enum e_error
{
	ERR_PIPEX_ALLOCATION_FAILURE,
	ERR_PIPEX_FORK_FAILURE,
	ERR_PIPEX_EXEC_FAILURE,
	ERR_PIPEX_ARG_COUNT,
	ERR_SHELL_CMD_NOT_FOUND,
	ERR_SHELL_FILE_NOT_FOUND,
	ERR_COUNT,
}	t_error;

// processes.c
int				execute_procs(t_pipex *pipex);

// free.c
void			free_cmds(t_cmd **cmds);
void			free_cmd(t_cmd *cmd);
void			free_split(char **s_split);

// utils.c
unsigned int	cmd_count(t_pipex *pipex);
char			**strjoin_free_2d(char **s_base, char **s_append);
int				cmds_get_runnable(t_cmd *cmd);

// parser.c
char			**parse_args(char *argv[]);
int				cmds_is_empty(char **argv, int count);

// commands.c
int				create_commands(t_pipex *pipex, char *args[], char **envp);
char			*find_path(char *envp[]);

// error.c
int				error_code_child_crash(int status);
void			error_exit(t_pipex *pipex, t_error err);
int				error_message(const char *s, char *cmd);
const char		*error_get_name(t_error err);

#endif
