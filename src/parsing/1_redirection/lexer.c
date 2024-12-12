/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:51:50 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/10 12:54:40 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	check_redir(char *in)
{
	int	i;
	int	status;
	int	nbr;

	i = 0;
	status = 0;
	nbr = 0;
	while (in[i])
	{
		status = in_quote(status, in[i]);
		if ((in[i] == '<' || in[i] == '>') && status == 0)
			nbr++;
		while (in[i] && (in[i] == '<' || in[i] == '>'))
			i++;
		i++;
	}
	return (nbr);
}

char	**add_redir(char **tab, char **to_add)
{
	char	**res;
	int		i;
	int		j;

	res = (char **)safe_malloc(sizeof(char *) * (nbr_of_line(tab) + nbr_of_line(to_add) + 1), ALLOC_COMMAND);
	i = 0;
    if (tab) {
        while (tab[i]) {
            res[i] = safe_strdup(tab[i], ALLOC_COMMAND);
            i++;
        }
    }
	j = 0;
	while (to_add[j])
	{
		res[i] = safe_strdup(to_add[j], ALLOC_COMMAND);
		i++;
		j++;
	}
	res[i] = NULL;
	return (res);
}

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
		status = in_quote(status, line[*start + *end]);
		(*end)++;
		while (line[*start + *end] && status != 0)
		{
			status = in_quote(status, line[*start + *end]);
			(*end)++;
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
			to_add = (char *)safe_malloc(sizeof(char) * (end + 1), ALLOC_COMMAND);
			ft_strlcpy(to_add, line + start, end + 1);
			res = add_line(res, to_add, ALLOC_COMMAND);
			free(to_add);
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
	//ft_free_tab(in);
	return (res);
}
