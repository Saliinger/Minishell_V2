/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_files.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 01:04:47 by ekrebs            #+#    #+#             */
/*   Updated: 2024/12/16 02:09:18 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	get_fd(t_redir *redir)
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
		return (perror("redir type unknown"), -1);
	if (fd < 0)
	{
		printerr("minishell: ");
		return (perror(redir->redir), -1);
	}
	return (fd);
}

static int get_last_fds(t_redir *redir, int *last_fd_in, int *last_fd_out)
{
	int fd;

	while (redir)
	{
		fd = get_fd(redir);
		if (fd == -1)
			return (-1);
		if (redir->type == R_INPUT || redir->type == R_HEREDOC)
		{
			if (*last_fd_in != -1)
				close(*last_fd_in);
			*last_fd_in = fd;
		}
		else if (redir->type == R_OUTPUT || redir->type == R_APPEND)
		{
			if (*last_fd_out != -1)
				close(*last_fd_out);
			*last_fd_out = fd;
		}
		else
			printerr("\n\tUnexpected redirection type.\n");
		redir = redir->next;
	}
	return (0);
}

static int	apply_last_redirs(int last_fd_in, int last_fd_out)
{
	unlink("temp_heredoc_file");
	if (last_fd_in != -1)
	{
		if (dup2(last_fd_in, STDIN_FILENO) < 0)
			return (perror("dup2 (in)"), close(last_fd_in), -1);
		close(last_fd_in);
	}
	if (last_fd_out != -1)
	{
		if (dup2(last_fd_out, STDOUT_FILENO) < 0)
			return (perror("dup2 (out)"), close(last_fd_out), -1);
		close(last_fd_out);
	}
	return (0);
}

int	handle_redirections(t_command *cmd)
{
	t_redir	*redir;
	int		err;
	int		last_fd_in;
	int		last_fd_out;

	last_fd_in = -1;
	last_fd_out = -1;
	redir = cmd->redirection;
	if (!redir)
		return (0);
	err = get_last_fds(redir, &last_fd_in, &last_fd_out);
	if (err)
		return (-1);
	return (apply_last_redirs(last_fd_in, last_fd_out));
}


