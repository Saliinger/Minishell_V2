/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess_heredocs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:42:48 by ekrebs            #+#    #+#             */
/*   Updated: 2024/12/16 21:47:25 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	handle_heredoc_exit(int saved_stdin, int fd, char *line, t_minishell *m)
{
	close(saved_stdin);
	close(fd);
	free(line);
	if (g_sig == SIGINT)
	{
		g_sig = NO_SIG;
		m->exit_status[0] = 130;
	}
}

int	do_the_heredoc(int fd, t_redir *redir, t_minishell *m)
{
	char	*line;
	int		saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin < 0)
		return (perror("dup stdin"), -1);
	while (1)
	{
		set_signals_to_heredoc();
		line = readline(" >");
		set_signals_to_ignore();
		if (g_sig == SIGINT)
		{
			dup2(saved_stdin, STDIN_FILENO);
			handle_heredoc_exit(saved_stdin, fd, line, m);
			return (0);
		}
		if (!line || ft_strcmp(line, redir->redir) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	handle_heredoc_exit(saved_stdin, fd, line, m);
}

int	handle_heredoc(t_redir *redir, t_minishell *m)
{
	int		fd;
	char	temp_file[128];
	int		hd_id;

	hd_id = 0;
	snprintf(temp_file, sizeof(temp_file), "temp_hd_%d", hd_id++);
	fd = open(temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("Erreur ouverture heredoc"), -1);
	do_the_heredoc(fd, redir, m);
	redir->redir = safe_strdup(temp_file, ALLOC_COMMAND);
	redir->type = R_INPUT;
	return (0);
}

int	preprocess_heredocs(t_command *cmd, t_minishell *m)
{
	t_redir	*redir;

	while (cmd)
	{
		redir = cmd->redirection;
		while (redir)
		{
			if (redir->type == R_HEREDOC)
			{
				if (handle_heredoc(redir, m) < 0)
					return (-1);
			}
			redir = redir->next;
		}
		cmd = cmd->subcommand;
	}
	return (0);
}
