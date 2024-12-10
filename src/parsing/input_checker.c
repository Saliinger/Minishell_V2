/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:35:28 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/06 23:03:56 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	quote_checker(char *in, char c)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (in[i])
	{
		if (in[i] == c)
		{
			flag = 1;
			i++;
			while (in[i] && in[i] != c)
				i++;
			if (in[i] == c)
				flag = 0;
		}
		i++;
	}
	if (flag == 1)
		return (printf("Error syntax: the %c is not closed. Go fuck yourself\n",
				c), false);
	return (true);
}

bool	divider_checker(char *in, char c)
{
	int	i;

	i = 0;
	while (in[i])
	{
		if (in[i] == c)
		{
			if (in[i + 1] == c && c == '|')
			{
				printf("Error syntax: too many %c. Are you really trying ?\n",
					c);
				return (false);
			}
			if (in[i + 1] == c && in[i + 2] == c && (c == '<' || c == '>'))
			{
				printf("Error syntax: too many %c. Are you really trying ?\n",
					c);
				return (false);
			}
		}
		i++;
	}
	return (true);
}

bool	extend_forbiden_checker(char *in, char c, char q, int *i)
{
	(void)c;
	while (in[*i] && in[*i] != q)
	{
		if (in[*i] == q)
			return (true);
		*i = *i + 1;
	}
	return (false);
}

bool	forbiden_checker(char *in, char c)
{
	int	i;

	i = 0;
	while (in[i])
	{
		if (in[i] != '\"' && extend_forbiden_checker(in, c, '\"', &i))
			return (false);
		if (in[i] != '\'' && extend_forbiden_checker(in, c, '\'', &i))
			return (false);
		else if (in[i] == c)
			return (false);
		i++;
	}
	return (true);
}

bool	input_checker(char *in)
{
	if (divider_checker(in, '<') && quote_checker(in, '\'')
		&& divider_checker(in, '>') && divider_checker(in, '|')
		&& quote_checker(in, '\"') && forbiden_checker(in, ';'))
		return (printf("true\n"), true);
	else
		return (false);
}
