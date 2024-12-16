/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess_heredocs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:42:48 by ekrebs            #+#    #+#             */
/*   Updated: 2024/12/16 20:59:27 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	preprocess_heredocs(t_command *cmd, t_minishell *m)
{
	t_redir	*redir;
	char	temp_file[128];
	int		fd;
	char	*line;
	int		hd_id;
	int		saved_stdin;

	hd_id = 0;
	while (cmd)
	{
		redir = cmd->redirection;
		while (redir)
		{
			if (redir->type == R_HEREDOC)
			{
				snprintf(temp_file, sizeof(temp_file), "temp_hd_%d", hd_id++);
				fd = open(temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd < 0)
					return (perror("Erreur ouverture heredoc"), -1);
				saved_stdin = dup(STDIN_FILENO);
				while (1)
				{
					set_signals_to_heredoc();
					line = readline(" >");
					set_signals_to_ignore();
					if (g_sig == SIGINT)
					{
						g_sig = NO_SIG;
						m->exit_status[0] = 130;
						dup2(saved_stdin, STDIN_FILENO);
						break ;
					}
					if (!line || ft_strcmp(line, redir->redir) == 0)
						break ;
					write(fd, line, ft_strlen(line));
					write(fd, "\n", 1);
					free(line);
				}
				close(saved_stdin);
				close(fd);
				free(line);
				redir->redir = safe_strdup(temp_file, ALLOC_COMMAND);
				redir->type = R_INPUT;
			}
			redir = redir->next;
		}
		cmd = cmd->subcommand;
	}
	return (0);
}
