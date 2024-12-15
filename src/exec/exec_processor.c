/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_processor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 00:07:20 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/16 00:51:03 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_fd(t_redir *redir)
{
	int	fd;

	fd = 0;
	if (redir->type == R_OUTPUT)
		fd = open(redir->redir, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == R_APPEND)
		fd = open(redir->redir, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == R_INPUT)
		fd = open(redir->redir, O_RDONLY);
	else if (redir->type == R_HEREDOC)
		fd = heredoc_handler(fd, redir);
	else
		return (perror("Type de redirection inconnu"), -1);
	if (fd < 0)
	{
		printerr("minishell: ");
		return (perror(redir->redir), -1);
	}
	return (fd);
}

static int	handle_redirections(t_command *cmd)
{
	t_redir	*redir;
	int		fd;

	redir = cmd->redirection;
	if (!redir)
		return (0);
	while (redir)
	{
		fd = get_fd(redir);
		if (fd == -1)
			return (-1);
		if (redir->type == R_INPUT || redir->type == R_HEREDOC)
		{
			if (redir->next && redir->next->type == R_HEREDOC)
				;
			else
				if (dup2(fd, STDIN_FILENO) < 0)
					return (perror("dup2 (entrée)"), close(fd), -1);
		}
		else
		{
			if (dup2(fd, STDOUT_FILENO) < 0)
				return (perror("dup2 (sortie)"), close(fd), -1);
		}
		close(fd);
		redir = redir->next;
	}
	unlink("temp_heredoc_file");
	return (0);
}

// potentiel solution
// static int	handle_redirections(t_command *cmd)
// {
// 	t_redir	*redir;
// 	int		fd;
// 	int		last_in;
// 	int		last_out;
//
// 	redir = cmd->redirection;
// 	if (!redir)
// 		return (0);
// 	last_in = -1;
// 	last_out = -1;
// 	while (redir)
// 	{
// 		fd = get_fd(redir);
// 		if (fd == -1)
// 			return (-1);
// 		if (redir->type == R_INPUT || redir->type == R_HEREDOC)
// 			last_in = fd;
// 		else
// 			last_out = fd;
// 		add_safe_fd(fd, OPEN_FD);
// 		redir = redir->next;
// 	}
// 	if (dup2(last_in, STDIN_FILENO) < 0)
// 		return (perror("dup2 (entrée)"), -1);
// 	if (dup2(last_out, STDOUT_FILENO) < 0)
// 		return (perror("dup2 (sortie)"), -1);
// 	unlink("temp_heredoc_file");
// 	return (0);
// }

void	process_fork(t_command *cmd, t_minishell *m)
{
	int		prev_pipe_fd;
	pid_t	pid;

	prev_pipe_fd = -1;
	while (cmd)
	{
		if (cmd->subcommand)
		{
			if (pipe(cmd->pipe_fds) < 0)
			{
				perror("Erreur de pipe");
				break ;
			}
		}
		pid = fork();
		if (pid < 0)
		{
			perror("Erreur lors du fork");
			break ;
		}
		else if (pid == 0)
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
			exit(ft_exec(m, cmd));
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
	int			status;
	t_command	*cmd;

	cmd = parsing(line, m);
	if (cmd == NULL)
		return ;
	if (count_cmd(cmd) == 1 && (cmd->id == EXIT_ID || cmd->id == CD_ID
			|| cmd->id == EXPORT_ID || cmd->id == UNSET_ID))
		ft_exec(m, cmd);
	else
	{
		process_fork(cmd, m);
		while (waitpid(-1, &status, 0) > 0)
		{
			if (WIFEXITED(status))
				m->exit_status[0] = WEXITSTATUS(status);
		}
	}
	safe_malloc(0, DESTROY_COMMAND);
}

// lors de la creation de work la subcommand est null donc affiche des messages d'erreur
// lors de l'execution simple les redirections ne sont pas gerer
