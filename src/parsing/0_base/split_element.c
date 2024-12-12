/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:24:12 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/09 18:25:52 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	ft_split_write_extend(size_t *i, size_t *j, const char *s, char c)
{
	int	status;

	status = 0;
	*j = 0;
	while (s[*i + *j] && s[*i + *j] != c && s[*i + *j] != '\t' && s[*i
			+ *j] != '\n')
	{
		if (s[*i + *j] == '\"' || s[*i + *j] == '\'')
		{
			status = in_quote(status, s[*i + *j]);
			(*j)++;
			while (s[*i + *j] && status != 0)
			{
				status = in_quote(status, s[*i + *j]);
				(*j)++;
			}
		}
		else
			(*j)++;
	}
}

static int	ft_split_write(char **dest, char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == c || s[i] == '\t' || s[i] == '\n'))
			i++;
		if (s[i])
		{
			ft_split_write_extend(&i, &j, s, c);
			if (j > 0)
			{
				*dest = (char *)safe_malloc(sizeof(char) * (j + 1), ALLOC_COMMAND);
				ft_split_write_word(*dest, s, i, j);
				dest++;
			}
			i += j;
		}
	}
	*dest = NULL;
	return (0);
}

char	**split_element(char *s, char c)
{
	char	**dest;

	if (!s)
		return (NULL);
	dest = (char **)safe_malloc(sizeof(char *) * (ft_countword(s, c) + 1), ALLOC_COMMAND);
	ft_split_write(dest, s, c);
	return (dest);
}
