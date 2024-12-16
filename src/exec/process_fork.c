/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 02:44:59 by ekrebs            #+#    #+#             */
/*   Updated: 2024/12/16 03:11:29 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int handle_heredocs(t_command *cmd, t_minishell *m)
{
	if (preprocess_heredocs(cmd, m) < 0)
	{
		printerr("minishell: error processing heredocs\n");
		return (-1);
	}
	return (0);
}

static int create_pipe(t_command *cmd)
{
	if (cmd->subcommand && pipe(cmd->pipe_fds) < 0)
	{
		perror("Erreur de pipe");
		return (-1);
	}
	return (0);
}

static void setup_child(t_command *cmd, int prev_pipe_fd)
{
	if (prev_pipe_fd != -1)
		dup2(prev_pipe_fd, STDIN_FILENO);
	if (cmd->subcommand)
		dup2(cmd->pipe_fds[1], STDOUT_FILENO);

	if (handle_redirections(cmd) < 0)
		exit(EXIT_FAILURE);

	if (prev_pipe_fd != -1)
		close(prev_pipe_fd);
	if (cmd->subcommand)
	{
		close(cmd->pipe_fds[0]);
		close(cmd->pipe_fds[1]);
	}
}

static void parent_cleanup(t_command *cmd, int *prev_pipe_fd)
{
	if (*prev_pipe_fd != -1)
		close(*prev_pipe_fd);
	if (cmd->subcommand)
		close(cmd->pipe_fds[1]);
	*prev_pipe_fd = cmd->pipe_fds[0];
}

static void wait_for_children(int *status, t_minishell *m)
{
	while (waitpid(-1, status, 0) > 0)
	{
		if (WIFEXITED(*status))
			m->exit_status[0] = WEXITSTATUS(*status);
	}
}

void process_fork(t_command *cmd, t_minishell *m, int *status)
{
	int prev_pipe_fd;
	pid_t pid;

	prev_pipe_fd = -1;
	if (handle_heredocs(cmd, m) < 0)
		return;

	while (cmd)
	{
		if (create_pipe(cmd) < 0)
			return;

		pid = fork();
		if (pid < 0)
		{
			perror("Erreur lors du fork");
			return;
		}
		if (pid == 0)
		{
			setup_child(cmd, prev_pipe_fd);
			exit(ft_exec(m, cmd));
		}
		parent_cleanup(cmd, &prev_pipe_fd);
		cmd = cmd->subcommand;
	}
	wait_for_children(status, m);
}
