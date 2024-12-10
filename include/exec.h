/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:13:52 by ekrebs            #+#    #+#             */
/*   Updated: 2024/11/30 03:31:18 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "minishell.h"

typedef struct s_minishell t_minishell;
typedef struct s_command t_command;
typedef struct s_redir t_redir;

# define IN		0
# define OUT	1

# define RE		0
# define WE		1

//-------
typedef struct s_pids
{
	pid_t			pid;
	struct s_pids	*next;
}					t_pids_llist_node, t_pids;


typedef	struct s_infos
{
	t_pids		*pids_llist;
	pid_t		last_pid;
	int			last_cmd_type;
	int			cmd_count;
	int			**pipes;
}			t_infos;

typedef struct s_command_exec
{
	int						index;				//init me to -1,
	int						cmd_id;				//init me to -1,		//fill me if builtin with the builtin id, else 0 if not builtin
	char					**cmd_args;			//init me to NULL		//file me with the execve tab
	t_redir					*redir_files_llist; //init me to NULL
	char					*last_heredoc_str;	//init me to NULL, 
	int						redir_fds[2];		//init as a tab of -1,	//parsing doesnt care about that
	struct s_command_exec	*next;				//init me to NULL
}		t_command_exec;



// FUNCTIONS LOCALISED TO EXEC
int		exec_builtin(t_command_exec *c, t_minishell *m, t_infos *i);
int		exec_loop(t_command_exec **cmds, t_minishell *m, t_infos *i);
pid_t	exec_extern(t_command_exec *cmds, t_minishell *m, t_infos *inf);
void	execve_command(t_command_exec *c, t_minishell *m, t_infos *i);
int		open_cmds_fds(t_command_exec *cmds, int *fds_last_redir);
int     apply_redirections(t_command_exec *cmd, t_infos *i);
int		get_exit_status(t_minishell *m, t_infos *i);
int		open_cmd_fds(t_command_exec *cmd, int *fds_last_redir);
int		save_std_fds(int *std_fds);
int		restore_std_fds(int *std_fds);
int		ft_close_saved_std_fds(int *std_fds);
int		resolve_all_heredocs(t_command_exec *cmds, t_minishell *m);
int		create_all_pipes(int cmd_count, int ***pipes_out);

int		ft_close_pipes(int pipe_count, int ***pipes);

//UTILS
int		parsing_restruct(t_command **old, t_command_exec **new);
int		restruct_stealing_from_old(t_command **old, t_command_exec **c);
int		reparse_redir_files_llist(t_command_exec *c);
void	restruct_discarding_old(t_command **o);
int		count_cmds(t_command_exec *cmd);
void	index_nodes(t_command_exec *c);

//parsing_restruct
void	print_t_exec_command(t_command_exec *command);

// t_pids functions
t_pids	*pids_addfront(t_pids *pids, pid_t pid);
void	free_pids(t_pids **pids_adr);
int		pids_size(t_pids *pids);

int		ft_close(int *fd);
int		ft_dup2(int fd, int fd2);
int		ft_dup(int fd);
#endif