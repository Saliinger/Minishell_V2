/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_processor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 00:07:20 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/16 03:02:15 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int preprocess_heredocs(t_command *cmd)
// {
// 	t_redir *redir;
// 	int     hd_id = 0; // Unique identifier for heredocs

// 	while (cmd)
// 	{
// 		redir = cmd->redirection;
// 		while (redir)
// 		{
// 			if (redir->type == R_HEREDOC)
// 			{
// 				char temp_file[128];
// 				snprintf(temp_file, sizeof(temp_file), "temp_hd_%d", hd_id++);
// 				int fd = open(temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 				if (fd < 0)
// 					return (perror("Erreur ouverture heredoc"), -1);

// 				char *line;
// 				while (1)
// 				{
// 					set_signals_to_minishell();
// 					line = readline(" >");
// 					set_signals_to_ignore();
// 					if (g_sig == SIGINT)
// 					{
// 						g_sig = 0;
// 						m->exit_status[0] = 130;
// 					}
// 					if (!line || ft_strcmp(line, redir->redir) == 0)
// 						break;
// 					write(fd, line, ft_strlen(line));
// 					write(fd, "\n", 1);
// 					free(line);
// 				}
// 				close(fd);
// 				free(line);

// 				// Replace heredoc redirection with input from the temp file
// 				free(redir->redir);
// 				redir->redir = ft_strdup(temp_file);
// 				redir->type = R_INPUT; // Change type to standard input redirection
// 			}
// 			redir = redir->next;
// 		}
// 		cmd = cmd->subcommand;
// 	}
// 	return (0);
// }

// void process_fork(t_command *cmd, t_minishell *m, int *status)
// {
// 	int prev_pipe_fd = -1; // File descriptor for the previous command's output
// 	pid_t pid;

// 	// Preprocess heredocs for the entire command chain
// 	if (preprocess_heredocs(cmd) < 0)
// 	{
// 		printerr("minishell: error processing heredocs\n");
// 		return;
// 	}

// 	while (cmd)
// 	{
// 		if (cmd->subcommand)
// 		{
// 			if (pipe(cmd->pipe_fds) < 0)
// 			{
// 				perror("Erreur de pipe");
// 				return;
// 			}
// 		}

// 		pid = fork();
// 		if (pid < 0)
// 		{
// 			perror("Erreur lors du fork");
// 			return;
// 		}

// 		if (pid == 0) // Child process
// 		{
// 			if (prev_pipe_fd != -1) // Read from previous pipe
// 				dup2(prev_pipe_fd, STDIN_FILENO);
// 			if (cmd->subcommand) // Write to the current pipe
// 				dup2(cmd->pipe_fds[1], STDOUT_FILENO);

// 			if (handle_redirections(cmd) < 0)
// 				exit(EXIT_FAILURE);

// 			// Close pipe ends in the child
// 			if (prev_pipe_fd != -1)
// 				close(prev_pipe_fd);
// 			if (cmd->subcommand)
// 			{
// 				close(cmd->pipe_fds[0]);
// 				close(cmd->pipe_fds[1]);
// 			}

// 			exit(ft_exec(m, cmd)); // Execute the command
// 		}

// 		// Parent process
// 		if (prev_pipe_fd != -1)
// 			close(prev_pipe_fd); // Close the previous pipe's read end
// 		if (cmd->subcommand)
// 			close(cmd->pipe_fds[1]); // Close the current pipe's write end
// 		prev_pipe_fd = cmd->pipe_fds[0]; // Save the current pipe's read end

// 		cmd = cmd->subcommand;
// 	}

// 	// Wait for all child processes
// 	while (waitpid(-1, status, 0) > 0)
// 	{
// 		if (WIFEXITED(*status))
// 			m->exit_status[0] = WEXITSTATUS(*status);
// 	}
// }


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
		process_fork(cmd, m, &status);
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
