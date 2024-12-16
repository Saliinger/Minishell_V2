/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:21:05 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/16 23:53:29 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	handle_redirection_symbols(char *line, int *start, int *end)
{
	(*end)++;
	while (line[*start + *end] && (line[*start + *end] == '<' \
												|| line[*start + *end] == '>'))
		(*end)++;
}

void	handle_quoted_section(char *line, int *start, int *end)
{
	int	status;

	status = 0;
	while (line[*start + *end] && line[*start + *end] != '<' \
				&& line[*start + *end] != '>' && line[*start + *end] == ' ' \
				&& line[*start + *end] != '\t' && line[*start + *end] != '\n')
	{
		if (line[*start + *end] == '\'' || line[*start + *end] == '\"')
		{
			status = in_quote(status, line[*start + *end]);
			(*end)++;
		}
		while (line[*start + *end] && status != 0)
		{
			status = in_quote(status, line[*start + *end]);
			(*end)++;
		}
	}
}

void	handle_unquoted_section(char *line, int *start, int *end)
{
	int	status;

	status = 0;
	while (line[*start + *end] && line[*start + *end] != '<' \
						&& line[*start + *end] != '>' && status == 0)
	{
		status = in_quote(status, line[*start + *end]);
		(*end)++;
	}
}
