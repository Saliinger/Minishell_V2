/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_processor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 00:07:20 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/16 05:34:53 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_fd(t_redir *redir)
{
	int	fd;
	char *msg;

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
		msg = ft_strjoin_safe(safe_strdup("minishell: ", ALLOC_COMMAND), redir->redir, ALLOC_COMMAND);
		return (perror(msg), -1);
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

int	preprocess_heredocs(t_command *cmd)
{
	t_redir	*redir;
	char	temp_file[128];
	int		fd;
	char	*line;
	int		hd_id;

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
				while (1)
				{
					line = readline(" >");
					if (!line || ft_strcmp(line, redir->redir) == 0)
						break ;
					write(fd, line, ft_strlen(line));
					write(fd, "\n", 1);
					free(line);
				}
				close(fd);
				free(line);
				free(redir->redir);
				redir->redir = ft_strdup(temp_file);
				redir->type = R_INPUT;
			}
			redir = redir->next;
		}
		cmd = cmd->subcommand;
	}
	return (0);
}

t_pids_list *pids_list_safe_addback(int pid, t_pids_list *first)
{
    t_pids_list *node;
    t_pids_list *new_node;

    new_node = safe_malloc(sizeof(t_pids_list), ALLOC_COMMAND);
    new_node->pid = pid;
    new_node->next = NULL;

    if (!first)
        return (new_node);

    node = first;
    while (node->next)
        node = node->next;

    node->next = new_node;
    return (first);
}

void	process_fork(t_command *cmd, t_minishell *m, t_pids_list **pids_list)
{
	pid_t	pid;
	int		prev_pipe_fd;

	prev_pipe_fd = -1;
	if (preprocess_heredocs(cmd) < 0)
	{
		printerr("minishell: error processing heredocs\n");
		return ;
	}
	while (cmd)
	{
		if (cmd->subcommand)
		{
			if (pipe(cmd->pipe_fds) < 0)
			{
				perror("Erreur de pipe");
				return ;
			}
		}
		pid = fork();
		if (pid < 0)
		{
			perror("Erreur lors du fork");
			return ;
		}
		if (pid == 0)
		{
			if (prev_pipe_fd != -1)
				dup2(prev_pipe_fd, STDIN_FILENO);
			if (cmd->subcommand)
				dup2(cmd->pipe_fds[1], STDOUT_FILENO);
			if (handle_redirections(cmd) < 0)
				nuclear_exit(EXIT_FAILURE);
			if (prev_pipe_fd != -1)
				close(prev_pipe_fd);
			if (cmd->subcommand)
			{
				close(cmd->pipe_fds[0]);
				close(cmd->pipe_fds[1]);
			}
			nuclear_exit(ft_exec(m, cmd));
		}
		else
		{
			*pids_list = pids_list_safe_addback(pid, *pids_list);
		}
		if (prev_pipe_fd != -1)
			close(prev_pipe_fd);
		if (cmd->subcommand)
			close(cmd->pipe_fds[1]);
		prev_pipe_fd = cmd->pipe_fds[0];
		cmd = cmd->subcommand;
	}
}

void get_exit_status(t_minishell *m, t_pids_list *pids)
{
	int			status;

	while(pids)
	{
		if (waitpid(pids->pid, &status, 0) > 0)
		{
			if (WIFEXITED(status))
				m->exit_status[0] = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				m->exit_status[0] = 128 + WTERMSIG(status);
		}
		pids = pids->next;
	}
}

void	process_input_line(char *line, t_minishell *m)
{
	t_command	*cmd;
	t_pids_list *pids_list;

	cmd = parsing(line, m);
	if (cmd == NULL)
		return ;
	if (count_cmd(cmd) == 1 && (cmd->id == EXIT_ID || cmd->id == CD_ID
			|| cmd->id == EXPORT_ID || cmd->id == UNSET_ID))
		ft_exec(m, cmd);
	else
	{
		pids_list = NULL;
		process_fork(cmd, m, &pids_list);
		get_exit_status(m, pids_list);
	}
	safe_malloc(0, DESTROY_COMMAND);
}

// lors de la creation de work la subcommand est
// null donc affiche des messages d'erreur
// lors de l'execution simple les redirections ne sont pas gerer
