/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:33:22 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/16 20:19:57 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	checker_command(char *in, char *command)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (in[i])
	{
		if (in[i] != command[j])
			break ;
		i++;
		j++;
	}
	if (i == ft_strlen(command))
		return (true);
	else
		return (false);
}

int	nbr_of_line(char **env)
{
	int	i;

	if (!env)
		return (0);
	i = 0;
	while (env[i])
		i++;
	return (i);
}

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

char	**add_line(char **tab, char *to_add, enum e_action action)
{
	char	**res;
	int		i;
	int		tab_size;

	if (!tab)
		tab_size = 0;
	else
		tab_size = nbr_of_line(tab);
	res = (char **)safe_malloc(sizeof(char *) * (tab_size + 2), action);
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
