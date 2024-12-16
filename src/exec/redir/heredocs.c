/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 00:10:57 by ekrebs            #+#    #+#             */
/*   Updated: 2024/12/16 03:08:50 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void do_the_heredoc(t_redir *redir, int fd, t_minishell *m, int saved_stdin)
{
	char *line;

	while (1)
	{
		set_signals_to_heredoc();
		line = readline(" >");
		set_signals_to_ignore();
		if (g_sig == SIGINT)
		{
			g_sig = 0;
			free(line);
			close(fd);
			dup2(saved_stdin, STDIN_FILENO);
			m->exit_status[0] = 130;
			break;
		}
		if (!line || ft_strcmp(line, redir->redir) == 0)
			break;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
}

static int handle_heredoc_redirection(t_redir *redir, int *hd_id, t_minishell *m)
{
	char temp_file[128];
	int fd;
	int saved_stdin;

	snprintf(temp_file, sizeof(temp_file), "temp_hd_%d", (*hd_id)++);
	fd = open(temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("Erreur ouverture heredoc"), -1);
	saved_stdin = dup(STDIN_FILENO);
	do_the_heredoc(redir, fd, m, saved_stdin);
	close(saved_stdin);
	close(fd);
	free(redir->redir);
	redir->redir = ft_strdup(temp_file);
	redir->type = R_INPUT;
	return (0);
}

static int process_heredoc_redirections(t_redir *redir, int *hd_id, t_minishell *m)
{
	while (redir)
	{
		if (redir->type == R_HEREDOC)
		{
			if (handle_heredoc_redirection(redir, hd_id, m) < 0)
				return (-1);
		}
		redir = redir->next;
	}
	return (0);
}

int preprocess_heredocs(t_command *cmd, t_minishell *m)
{
	int hd_id;

	hd_id = 0;
	while (cmd)
	{
		if (process_heredoc_redirections(cmd->redirection, &hd_id, m) < 0)
			return (-1);
		cmd = cmd->subcommand;
	}
	return (0);
}

