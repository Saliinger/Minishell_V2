/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:33:22 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/10 17:43:43 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	in_quote(int status, char type)
{
	if (type == '\"' && status == 0)
		return (1);
	else if (type == '\'' && status == 0)
		return (-1);
	else if ((type == '\"' && status == 1) || (type == '\'' && status == -1))
		return (0);
	return (status);
}

static void	copy_tab(char **tab, char **res, char *to_add, enum e_action action)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		res[i] = safe_strdup(tab[i], action);
		i++;
	}
	res[i] = safe_strdup(to_add, action);
	res[i + 1] = NULL;
}

char	** add_line(char **tab, char *to_add, enum e_action action)
{
	char	**res;
	int		i;
	int		tab_size;

	if (!tab)
		tab_size = 0;
	else
		tab_size = nbr_of_line(tab);
	res = (char **)safe_malloc(sizeof(char *) * (tab_size + 2), action);
	if (!res)
		return (ft_free_tab(tab), NULL);
	i = 0;
	if (tab)
		copy_tab(tab, res, to_add, action);
	else
	{
		res[i] = safe_strdup(to_add, action);
		res[i + 1] = NULL;
	}
	return (res);
}
