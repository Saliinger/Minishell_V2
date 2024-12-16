/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:51:50 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/17 00:10:11 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// split all the weird redir case like <<sdf > sdf >asd <sdf etc

void	extend_get_redir(char *line, int *start, int *end)
{
	int	status;

	status = 0;
	if (line[*start + *end] == '<' || line[*start + *end] == '>')
	{
		(*end)++;
		while (line[*start + *end] && (line[*start + *end] == '<' || line[*start
				+ *end] == '>'))
			(*end)++;
		return ;
	}
	else if (line[*start + *end] == '\'' || line[*start + *end] == '\"')
	{
		while (line[*start + *end] && line[*start + *end] != '<' && line[*start
			+ *end] != '>' && line[*start + *end] != ' ' && line[*start
			+ *end] != '\t' && line[*start + *end] != '\n')
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
		return ;
	}
	else
	{
		while (line[*start + *end] && line[*start + *end] != '<' && line[*start
			+ *end] != '>' && status == 0)
		{
			status = in_quote(status, line[*start + *end]);
			(*end)++;
		}
		return ;
	}
}

static char	**get_redir(char *line)
{
	char	**res;
	int		start;
	int		end;
	char	*to_add;

	start = 0;
	end = 0;
	res = NULL;
	while (line[start])
	{
		extend_get_redir(line, &start, &end);
		if (end > 0)
		{
			to_add = (char *)safe_malloc(sizeof(char) * (end + 1),
					ALLOC_COMMAND);
			ft_strlcpy(to_add, line + start, end + 1);
			res = add_line(res, to_add, ALLOC_COMMAND);
			start += end;
			end = 0;
		}
		else
			start++;
	}
	if (line[start])
		res = add_line(res, line + start, ALLOC_COMMAND);
	return (res);
}

char	**relexer(char **in)
{
	char	**res;
	char	**to_add;
	int		i;

	i = 0;
	res = NULL;
	while (in[i])
	{
		if (check_redir(in[i]) > 0)
		{
			to_add = get_redir(in[i]);
			res = add_redir(res, to_add);
		}
		else
			res = add_line(res, in[i], ALLOC_COMMAND);
		i++;
	}
	return (res);
}
