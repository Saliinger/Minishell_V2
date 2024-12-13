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

static int get_line(char **line, char *prompt, t_minishell *m)
{
	line[0] = readline(prompt);
	if (g_sig == SIGINT)
	{
		g_sig = 0;
		m->exit_status[0] = 130;
	}
	if (line[0] == NULL)
		return (free(*line), EXIT_EOF);
	else if (line[0][0] == '\0')
		*m->exit_status = 0;
	else
		add_history(line[0]);
	return (EXIT_SUCCESS);
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
        {
            process_input_line(line, m);
            free(line);
        }
        //break ; // pour le debug des leaks
    }
    if (prompt)
        free(prompt);
    return (EXIT_SUCCESS);
}
