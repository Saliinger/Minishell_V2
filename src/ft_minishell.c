/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 03:21:06 by ekrebs            #+#    #+#             */
/*   Updated: 2024/12/16 03:13:34 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	get_line(char **line, char *prompt, t_minishell *m)
{
	set_signals_to_minishell();
	line[0] = readline(prompt);
	set_signals_to_ignore();
	if (g_sig == SIGINT)
	{
		g_sig = 0;
		m->exit_status[0] = 130;
	}
	if (line[0] == NULL)
		return (free(*line), EXIT_EOF);
	else if (ft_strlen(*line) == 0)
		*m->exit_status = 0;
	else
		add_history(line[0]);
	return (EXIT_SUCCESS);
}

int	ft_minishell(t_minishell *m)
{
	char	*line;

	line = NULL;
	using_history();
	while (1)
	{
		if (get_line(&line, "\033[0;34mMinishell >$ \033[0m", m) == EXIT_EOF)
			return (EXIT_EOF);
		if (line && ft_strlen(line) > 0 && input_checker(m, line) == true)
			process_input_line(line, m);
		if (line)
			free(line);
	}
	return (EXIT_SUCCESS);
}
