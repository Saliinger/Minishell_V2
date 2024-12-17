/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_constructor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:37:06 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/17 02:40:30 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// init path handle the start of the path that we wan't to go to ~ / or nothing

static int	init_path(char *in, t_minishell *minishell, char **new_in)
{
	char	*temp;

	temp = get_current_path(minishell);
	temp = ft_strjoin_safe(temp, "/", ALLOC_COMMAND);
	*new_in = ft_strjoin_safe(temp, in, ALLOC_COMMAND);
	return (0);
}

bool	check_dot(char *in)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	if (!in)
		return (0);
	while (in[i])
	{
		if (in[i] == '.')
			nbr++;
		while (in[i] == '.')
			i++;
		i++;
	}
	return (nbr);
}

int	nbr_of_dot(char *line)
{
	int	nbr;

	nbr = 0;
	while (line[nbr] == '.')
		nbr++;
	return (nbr);
}

char	*get_res(char *current_path)
{
	char	*res;

	res = NULL;
	if (ft_strlen(current_path) > 0)
		res = (char *)safe_strdup(current_path, ALLOC_COMMAND);
	else
		res = (char *)safe_strdup("/", ALLOC_COMMAND);
	current_path = NULL;
	return (res);
}

char	*path_constructor(t_minishell *minishell, char *in)
{
	char	*res;
	char	*new_in;
	char	*current_path;
	int		i;
	char	**in_cut;

	i = init_path(in, minishell, &new_in);
	if (!check_dot(new_in))
		return (new_in);
	in_cut = ft_split_safe(new_in, '/', ALLOC_COMMAND);
	current_path = (char *)safe_malloc(sizeof(char) * PATH_MAX + 1,
			ALLOC_COMMAND);
	*current_path = '\0';
	while (in_cut[i])
	{
		if (check_dot(in_cut[i]))
		{
			if (nbr_of_dot(in_cut[i]) == 2)
				remove_path(current_path);
		}
		else
			add_path(current_path, in_cut[i]);
		i++;
	}
	res = get_res(current_path);
	return (res);
}
