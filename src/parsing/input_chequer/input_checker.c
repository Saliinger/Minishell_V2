/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@42mulhouse.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:58:21 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/11 17:58:21 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool	quote_checker(char *in, char c)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (in[i])
	{
        flag = in_quote(flag, in[i]);
		i++;
	}
	if (flag != 0)
		return (printerr("Error syntax: the %c is not closed. Go fuck yourself\n",
				c), false);
	return (true);
}

bool	divider_checker(char *in, char c)
{
	int	i;
    int status;

	i = 0;
    status = 0;
	while (in[i])
	{

        status = in_quote(status, in[i]);
        if (in[i + 1] == c && c == '|' && status == 0)
        {
            printerr("Error syntax: too many %c. Are you really trying ?\n",
                c);
            return (false);
        }

		i++;
	}
	return (true);
}

bool	forbiden_checker(char *in, char c)
{
	int	i;
    int status;

	i = 0;
    status = 0;
	while (in[i])
	{
        status = in_quote(status, in[i]);
		if (in[i] == c && status == 0)
		{
            printerr("Error syntax: too many %c. Are you really trying ?\n",
                c);
            return (false);
		}
		i++;
	}
	return (true);
}



bool check_start(char *s, char c)
{
    int i = 0;

    while (s[i] && (s[i] == '\n' || s[i] == '\t' || s[i] == ' '))
        i++;
    if (s[i] == c)
        return (printerr(" syntax error near unexpected token `%c'\n", c), false);
    return (true);
}

bool check_end(char *s, char c)
{
    int i = 0;

    i = ft_strlen(s) - 1;
    while (s[i] && (s[i] == '\n' || s[i] == '\t' || s[i] == ' '))
        i--;
    if (s[i] == c)
        return (printerr(" syntax error near unexpected token `%c'\n", c), false);
    return (true);
}

bool input_checker(t_minishell *minishell, char *command)
{
	if (!check_start(command, '|')
    || !check_start(command, '>')
    || !check_end(command, '|')
    || !check_end(command, '<')
    || !quote_checker(command, '\"')
    || !quote_checker(command, '\''))
        return (minishell->exit_status[0] = 2, false);
    return (true);
}
