/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 00:10:57 by ekrebs            #+#    #+#             */
/*   Updated: 2024/12/16 00:48:14 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	heredoc_loop(int fd, int duped_std_fd, char *delimiter)
{
	char	*line;

	line = NULL;
	while (1)
	{
		if (set_signals_to_heredoc() < 0)
			break ;
		line = readline("> ");
		if (set_signals_to_ignore() < 0)
			break ;
		if (g_sig == SIGINT)
		{
			g_sig = NO_SIG;
			dup2(duped_std_fd, STDIN_FILENO);
			break ;
		}
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

int	heredoc_handler(int fd, t_redir *redir)
{
	char	*delimiter;
	char	*temp_file;
	int		duped_std_in;
	
	delimiter = redir->redir;
	temp_file = "temp_heredoc_file";
	fd = open(temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("Erreur ouverture heredoc"), -1);
	duped_std_in = dup(STDIN_FILENO);
	heredoc_loop(fd, duped_std_in, delimiter);
	close(duped_std_in);
	close(fd);
	fd = open(temp_file, O_RDONLY);
	if (fd < 0)
		return (perror("Erreur ouverture fichier heredoc"), -1);
	return (fd);
}
