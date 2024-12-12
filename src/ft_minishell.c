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
		*m->exit_status = 0;
	else
		add_history(line[0]);
	return (EXIT_SUCCESS);
}

void heredoc_handler(char *line, int fd, char *delimiter)
{
    while (1)
    {
        line = readline("> ");
        if (!line || ft_strcmp(line, delimiter) == 0)
            break;
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    close(fd);
}

#define ON true
#define OFF false
#define PARSING_LEAK_TRACKING OFF

static int handle_redirections(t_command *cmd)
{
    t_redir *redir = cmd->redirection;
    int fd;

    while (redir)
    {
        if (redir->type == R_OUTPUT)
            fd = open(redir->redir, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else if (redir->type == R_APPEND)
            fd = open(redir->redir, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else if (redir->type == R_INPUT)
            fd = open(redir->redir, O_RDONLY);
        else if (redir->type == R_HEREDOC)
        {
            char *delimiter = redir->redir;
            char *temp_file = "temp_heredoc_file";

            fd = open(temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
                return (perror("Erreur ouverture heredoc"), -1);
            char *line = NULL;
            heredoc_handler(line, fd, delimiter);
            fd = open(temp_file, O_RDONLY);
            if (fd < 0)
                return (perror("Erreur ouverture fichier heredoc"), -1);
        }
        else
            return (perror("Type de redirection inconnu"), -1);

        if (fd < 0)
            return (perror(redir->redir), -1);

        if (redir->type == R_INPUT || redir->type == R_HEREDOC)
        {
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

static void process_input_line(char *line, t_minishell *m)
{
    int status;
    int pipe_fds[2];
    int prev_pipe_fd = -1;
    pid_t pid;
    t_command *cmd = parsing(line, m);

    if ( cmd == NULL)
        return ;
    if (count_cmd(cmd) == 1 && (cmd->id == EXIT_ID || cmd->id == CD_ID || cmd->id == EXPORT_ID || cmd->id == UNSET_ID))
    {
        ft_exec(m, cmd);
        return;
    }
    while (cmd)
    {
        if (cmd->subcommand && pipe(pipe_fds) < 0)
        {
            perror("Erreur de pipe");
            break;
        }
        pid = fork();
        if (pid < 0)
        {
            perror("Erreur lors du fork");
            break;
        }
        else if (pid == 0)
        {
            if (prev_pipe_fd != -1)
                dup2(prev_pipe_fd, STDIN_FILENO);
            if (cmd->subcommand)
                dup2(pipe_fds[1], STDOUT_FILENO);

            if (handle_redirections(cmd) < 0)
                exit(EXIT_FAILURE);

            if (prev_pipe_fd != -1)
                close(prev_pipe_fd);
            if (cmd->subcommand)
            {
                close(pipe_fds[0]);
                close(pipe_fds[1]);
            }
            exit(ft_exec(m, cmd));
        }
        if (prev_pipe_fd != -1)
            close(prev_pipe_fd);
        if (cmd->subcommand)
            close(pipe_fds[1]);
        prev_pipe_fd = pipe_fds[0];
        cmd = cmd->subcommand;
    }
     while (waitpid(-1, &status, 0) > 0)
     {
         if (WIFEXITED(status))
             m->exit_status[0] = WEXITSTATUS(status);
     }
    safe_malloc(0, DESTROY_COMMAND);
}

int ft_minishell(t_minishell *m)
{
    char *line;
    char *prompt;

    line = NULL;
    prompt = NULL;
    using_history();
    while (1)
    {
        prompt = display_prompt(prompt, m);
        if (get_line(&line, prompt, m) == EXIT_EOF)
            return (free(prompt), EXIT_EOF );
        if (line && line[0] != '\0' && input_checker(m, line) == true)
            process_input_line(line, m);
    }
    return (EXIT_SUCCESS);
}
