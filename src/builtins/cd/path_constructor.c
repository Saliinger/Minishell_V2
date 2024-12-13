/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_constructor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:37:06 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/10 15:32:09 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// init path handle the start of the path that we wan't to go to ~ / or nothing
static int	init_path(char *in, t_minishell *minishell, char **new_in)
{
	char	*temp;

	if (*in == '~' || *in == '/' || !in)
	{
		temp = get_home(&minishell);
		if (*in != '~' && ft_strcmp(temp, in) != 0)
			*new_in = ft_strjoin_safe(temp, in, ALLOC_COMMAND);
		else if (ft_strcmp(temp, in) != 0)
			*new_in = ft_strjoin_safe(temp, in + 1, ALLOC_COMMAND);
		else
			*new_in = safe_strdup(in, ALLOC_COMMAND);
	}
	else
	{
		temp = get_current_path(minishell);
		if (ft_strcmp(temp, in) != 0)
		{
			if (*in != '/')
				temp = ft_strjoin_safe(temp, "/", ALLOC_COMMAND);
			*new_in = ft_strjoin(temp, in);
		}
		else
			*new_in = ft_strdup(in);
	}
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
		res = safe_strdup(current_path, ALLOC_COMMAND);
	else
		res = safe_strdup("/", ALLOC_COMMAND);
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
	in_cut = ft_split(new_in, '/');
	current_path = (char *) safe_malloc(sizeof(char) * PATH_MAX + 1, ALLOC_COMMAND);
	while (in_cut[i])
	{
		if (ft_strlen(in_cut[i]) <= 3 && *in_cut[i] == '.')
		{
			if (nbr_of_dot(in_cut[i]) == 2)
				remove_path(current_path);
			else if (nbr_of_dot(in_cut[i]) > 2)
				add_path(current_path, in_cut[i]);
		}
		else
			add_path(current_path, in_cut[i]);
		i++;
	}
	res = get_res(current_path);
	return (res);
}
