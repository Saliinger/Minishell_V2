/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:51:50 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/16 23:23:38 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// split all the weird redir case like <<sdf > sdf >asd <sdf etc

void	extend_get_redir(char *line, int *start, int *end)
{
	if (line[*start + *end] == '<' || line[*start + *end] == '>')
		handle_redirection_symbols(line, start, end);
	else if (line[*start + *end] == '\'' || line[*start + *end] == '\"')
		handle_quoted_section(line, start, end);
	else
		handle_unquoted_section(line, start, end);
}

static char	*extract_substring(char *line, int start, int end)
{
	char	*substring;

	substring = (char *)safe_malloc(sizeof(char) * (end + 1), ALLOC_COMMAND);
	ft_strlcpy(substring, line + start, end + 1);
	return (substring);
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
			to_add = extract_substring(line, start, end);
			res = add_line(res, to_add, ALLOC_COMMAND);
			start += end;
			end = 0;
		}
		else
			start++;
	}
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
