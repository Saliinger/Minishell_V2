/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:19:18 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/16 23:19:23 by anoukan          ###   ########.fr       */
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
		{
			nbr++;
			while (in[i] && (in[i] == '<' || in[i] == '>'))
			{
				if (in[i + 1] == '\0')
					break ;
				i++;
			}
		}
		i++;
	}
	return (nbr);
}

char	**add_redir(char **tab, char **to_add)
{
	char	**res;
	int		i;
	int		j;

	res = (char **)safe_malloc(sizeof(char *) * (nbr_of_line(tab)
				+ nbr_of_line(to_add) + 1), ALLOC_COMMAND);
	i = 0;
	if (tab)
	{
		while (tab[i])
		{
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
