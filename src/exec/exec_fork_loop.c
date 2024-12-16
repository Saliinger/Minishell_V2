/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:31:33 by ekrebs            #+#    #+#             */
/*   Updated: 2024/12/16 23:55:10 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_child_process(int prev_pipe_fd, t_command *cmd, \
																t_minishell *m)
{
	if (prev_pipe_fd != -1)
		dup2(prev_pipe_fd, STDIN_FILENO);
	if (cmd->subcommand)
		dup2(cmd->pipe_fds[1], STDOUT_FILENO);
	if (handle_redirections(cmd) < 0)
	{
		if (cmd->subcommand)
		{
			close(cmd->pipe_fds[0]);
			close(cmd->pipe_fds[1]);
		}
		nuclear_exit(EXIT_FAILURE);
	}
	if (prev_pipe_fd != -1)
		close(prev_pipe_fd);
	if (cmd->subcommand)
	{
		close(cmd->pipe_fds[0]);
		close(cmd->pipe_fds[1]);
	}
	nuclear_exit(ft_exec(m, cmd));
}

static void	handle_parent_process(t_pids_list **pids_list, pid_t pid, \
											int prev_pipe_fd, t_command *cmd)
{
	*pids_list = pids_list_safe_addback(pid, *pids_list);
	if (prev_pipe_fd != -1)
		close(prev_pipe_fd);
	if (cmd->subcommand)
		close(cmd->pipe_fds[1]);
}

static void	handle_fork_failure(t_command *cmd)
{
	perror("fork error");
	if (cmd->subcommand)
	{
		close(cmd->pipe_fds[0]);
		close(cmd->pipe_fds[1]);
	}
	nuclear_exit(EXIT_FAILURE);
}

static void	process_fork_loop(t_command *cmd, t_minishell *m, \
									t_pids_list **pids_list, int prev_pipe_fd)
{
	pid_t	pid;

	while (cmd)
	{
		if (cmd->subcommand)
		{
			if (pipe(cmd->pipe_fds) < 0)
			{
				perror("pipe error");
				nuclear_exit(EXIT_FAILURE);
			}
		}
		pid = fork();
		if (pid < 0)
			handle_fork_failure(cmd);
		if (pid == 0)
			handle_child_process(prev_pipe_fd, cmd, m);
		else
			handle_parent_process(pids_list, pid, prev_pipe_fd, cmd);
		prev_pipe_fd = cmd->pipe_fds[0];
		cmd = cmd->subcommand;
	}
}

void	process_fork(t_command *cmd, t_minishell *m, t_pids_list **pids_list)
{
	int	prev_pipe_fd;

	prev_pipe_fd = -1;
	if (preprocess_heredocs(cmd, m) < 0)
	{
		printerr("minishell: error processing heredocs\n");
		nuclear_exit(EXIT_FAILURE);
	}
	process_fork_loop(cmd, m, pids_list, prev_pipe_fd);
	if (prev_pipe_fd != -1)
		close(prev_pipe_fd);
}
