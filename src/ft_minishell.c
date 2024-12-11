/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 03:21:06 by ekrebs            #+#    #+#             */
/*   Updated: 2024/12/07 10:46:33 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	get_line(char **line, char *prompt, t_minishell *m)
{
	line[0] = readline(prompt);
	if (g_sig == SIGINT)
	{
		g_sig = 0;
		m->exit_status[0] = 130;
	}
	if (line[0] == NULL)
		return (EXIT_EOF);
	else if (line[0][0] == '\0')
		m->exit_status[0] = 0;
	else
		add_history(line[0]);
	return (EXIT_SUCCESS);
}

#define ON true
#define OFF false
#define PARSING_LEAK_TRACKING OFF

/**
 * brief : adds the line to history, parses it,
	executes it then returns exit status
 *
 *  */
static void	process_input_line(char *line, t_minishell *m)
{
	int		i = 0;
	int		status;
	int		pipe_fds[2];
	int		prev_pipe_fd = -1;
	pid_t	pid;
	char	**splited_cmd;

	splited_cmd = ft_split(line, '|');
	if (!splited_cmd)
		return ;
	while (splited_cmd[i])
	{
		if (splited_cmd[i + 1] && pipe(pipe_fds) < 0) {
			perror("Erreur de pipe");
			break;
		}
		pid = fork();
		if (pid < 0) {
			perror("Erreur lors du fork");
			break;
		}
		else if (pid == 0) {
			if (prev_pipe_fd != -1)
				dup2(prev_pipe_fd, STDIN_FILENO);
			if (splited_cmd[i + 1]) 
				dup2(pipe_fds[1], STDOUT_FILENO);
			if (prev_pipe_fd != -1)
				close(prev_pipe_fd);
			if (splited_cmd[i + 1]) {
				close(pipe_fds[0]);
				close(pipe_fds[1]);
			}
			ft_exec(m, parsing(splited_cmd[i], m));
			exit(EXIT_FAILURE);
		}
		if (prev_pipe_fd != -1)
			close(prev_pipe_fd);
		if (splited_cmd[i + 1])
			close(pipe_fds[1]);
		prev_pipe_fd = pipe_fds[0];
		i++;
	}
	while (waitpid(-1, &status, 0) > 0) {
		if (WIFEXITED(status))
			m->exit_status[0] = WEXITSTATUS(status);
	}
	for (i = 0; splited_cmd[i]; i++)
		free(splited_cmd[i]);
	free(splited_cmd);
}


int	ft_minishell(t_minishell *m)
{
	char	*line;
	char	*prompt;

	line = NULL;
	prompt = NULL;
	using_history();
	while (1)
	{
		prompt = display_prompt(prompt, m);
		get_line(&line, prompt, m);
		if (!line)
			return (free(prompt), EXIT_EOF);
		else
			process_input_line(line, m);
	}
	return (EXIT_SUCCESS);
}
