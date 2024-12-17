/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relexer_handle_cases.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:21:05 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/17 01:02:44 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	relexer_handle_redirection(char *line, int *start, int *end)
{
	(*end)++;
	while (line[*start + *end] && (line[*start + *end] == '<' \
												|| line[*start + *end] == '>'))
		(*end)++;
}

void	relexer_handle_quotes(char *line, int *start, int *end, int *status)
{
	while (line[*start + *end] && line[*start + *end] != '<' \
				&& line[*start + *end] != '>' && line[*start + *end] != ' ' \
				&& line[*start + *end] != '\t' && line[*start + *end] != '\n')
	{
		if (line[*start + *end] == '\'' || line[*start + *end] == '\"')
		{
			*status = in_quote(*status, line[*start + *end]);
			(*end)++;
		}
		while (line[*start + *end] && *status != 0)
		{
			*status = in_quote(*status, line[*start + *end]);
			(*end)++;
		}
	}
}

void	relexer_handle_default(char *line, int *start, int *end, int *status)
{
	while (line[*start + *end] && line[*start + *end] != '<' \
								&& line[*start + *end] != '>' && *status == 0)
	{
		*status = in_quote(*status, line[*start + *end]);
		(*end)++;
	}
}
