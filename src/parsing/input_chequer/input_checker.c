/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:58:21 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/17 02:12:32 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// check if there's any synthax error or unauthorize test like
// || ;
// < < < etc get fucked super tester

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
	{
		printerr("Error syntax: the %c is not closed. Go fuck yourself\n", c);
		return (false);
	}
	return (true);
}

bool	divider_checker(char *in, char c)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (in[i])
	{
		status = in_quote(status, in[i]);
		if (in[i + 1] == c && c == '|' && status == 0)
		{
			printerr("Error syntax: too many %c. Are you really trying ?\n", c);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	forbiden_checker(char *in, char c)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (in[i])
	{
		status = in_quote(status, in[i]);
		if (in[i] == c && status == 0)
		{
			printerr("Error syntax: too many %c. Are you really trying ?\n", c);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	check_start_end(char *s, char c, bool ends)
{
	int	i;

	if (ends == true)
		i = 0;
	else
		i = ft_strlen(s) - 1;
	while (i > 0 && s[i] && (s[i] == '\n' || s[i] == '\t' || s[i] == ' '))
	{
		if (ends == true)
			i++;
		else
			i--;
	}
	if (s[i] == c)
		return (printerr(" syntax error near unexpected token `%c'\n", c),
			false);
	return (true);
}

bool	input_checker(t_minishell *minishell, char *command)
{
	if (!check_start_end(command, '|', true) || !check_start_end(command, '>',
			true) || !check_start_end(command, '|', false)
		|| !check_start_end(command, '<', false) || !quote_checker(command,
			'\"') || !quote_checker(command, '\''))
		return (minishell->exit_status[0] = 2, false);
	return (true);
}
