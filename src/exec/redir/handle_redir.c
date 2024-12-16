/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:54:35 by ekrebs            #+#    #+#             */
/*   Updated: 2024/12/16 20:22:52 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	get_fd(t_redir *redir)
{
	int		fd;
	char	*msg;

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
		msg = ft_strjoin_safe(safe_strdup("minishell: ", ALLOC_COMMAND),
				redir->redir, ALLOC_COMMAND);
		return (perror(msg), -1);
	}
	return (fd);
}

int	handle_redirections(t_command *cmd)
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
			if (dup2(fd, STDIN_FILENO) < 0)
				return (perror("dup2 (input)"), close(fd), -1);
		}
		else
		{
			if (dup2(fd, STDOUT_FILENO) < 0)
				return (perror("dup2 (output)"), close(fd), -1);
		}
		close(fd);
		redir = redir->next;
	}
	return (0);
}
