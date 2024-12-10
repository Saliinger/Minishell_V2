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
	t_command	*c;

	c = parsing(line, m);
	if (PARSING_LEAK_TRACKING)
	{
		free_command(c);
		printerr("%s\n\tPARSING_LEAK_TRACKING: ON !%s\n\t\toutput is now %p. (destroyed via free_t_command).\n\n", 
		AINSI_BLUE, AINSI_RESET, c);
	}
	else
		m->exit_status[0] = ft_exec(&c, m);
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
		else if (*line)
			process_input_line(line, m);
		if (restore_std_fds(m->std_fds) == -1)
			return (free(prompt), ERR);
		// break ; //temporaire si tu veux tester un seul input
	}
	return (EXIT_SUCCESS);
}
