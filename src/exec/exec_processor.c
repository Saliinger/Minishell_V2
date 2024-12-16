/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_processor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 00:07:20 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/16 20:48:50 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	process_fork(t_command *cmd, t_minishell *m, t_pids_list **pids_list)
{
	pid_t	pid;
	int		prev_pipe_fd;

	prev_pipe_fd = -1;
	if (preprocess_heredocs(cmd, m) < 0)
	{
		printerr("minishell: error processing heredocs\n");
		return ;
	}
	while (cmd)
	{
		if (cmd->subcommand)
		{
			if (pipe(cmd->pipe_fds) < 0)
			{
				perror("Erreur de pipe");
				return ;
			}
		}
		pid = fork();
		if (pid < 0)
		{
			perror("Erreur lors du fork");
			return ;
		}
		if (pid == 0)
		{
			if (prev_pipe_fd != -1)
				dup2(prev_pipe_fd, STDIN_FILENO);
			if (cmd->subcommand)
				dup2(cmd->pipe_fds[1], STDOUT_FILENO);
			if (handle_redirections(cmd) < 0)
				nuclear_exit(EXIT_FAILURE);
			if (prev_pipe_fd != -1)
				close(prev_pipe_fd);
			if (cmd->subcommand)
			{
				close(cmd->pipe_fds[0]);
				close(cmd->pipe_fds[1]);
			}
			nuclear_exit(ft_exec(m, cmd));
		}
		else
		{
			*pids_list = pids_list_safe_addback(pid, *pids_list);
		}
		if (prev_pipe_fd != -1)
			close(prev_pipe_fd);
		if (cmd->subcommand)
			close(cmd->pipe_fds[1]);
		prev_pipe_fd = cmd->pipe_fds[0];
		cmd = cmd->subcommand;
	}
}

void	process_input_line(char *line, t_minishell *m)
{
	t_command	*cmd;
	t_pids_list	*pids_list;

	cmd = parsing(line, m);
	if (cmd == NULL)
		return ;
	if (count_cmd(cmd) == 1 && (cmd->id == EXIT_ID || cmd->id == CD_ID
			|| cmd->id == EXPORT_ID || cmd->id == UNSET_ID))
		ft_exec(m, cmd);
	else
	{
		pids_list = NULL;
		process_fork(cmd, m, &pids_list);
		get_exit_status(m, pids_list);
	}
	safe_malloc(0, DESTROY_COMMAND);
}
