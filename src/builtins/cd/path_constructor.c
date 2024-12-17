/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_constructor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:37:06 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/17 02:53:43 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// Initialize path by constructing the base path
static int	init_path(char *in, t_minishell *minishell, char **new_in)
{
	char	*temp;

	temp = get_current_path(minishell);
	temp = ft_strjoin_safe(temp, "/", ALLOC_COMMAND);
	*new_in = ft_strjoin_safe(temp, in, ALLOC_COMMAND);
	return (0);
}

// Check if a string contains dots only and return a boolean
bool	check_dot(char *in)
{
	int	i;

	if (!in)
		return (false);
	i = 0;
	while (in[i])
	{
		if (in[i] != '.')
			return (false);
		i++;
	}
	return (true);
}

// Count the number of consecutive dots at the start of the string
int	nbr_of_dot(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i] && line[i] == '.')
		i++;
	return (i);
}

// Safely return the final resolved path
char	*get_res(char *current_path)
{
	if (ft_strlen(current_path) > 0)
		return (safe_strdup(current_path, ALLOC_COMMAND));
	return (safe_strdup("/", ALLOC_COMMAND));
}

// Main path constructor logic
char	*path_constructor(t_minishell *minishell, char *in)
{
	char	*res;
	char	*new_in;
	char	*current_path;
	char	**in_cut;
	int		i;

	init_path(in, minishell, &new_in);
	if (!ft_strchr(new_in, '.'))
		return (new_in);
	in_cut = ft_split_safe(new_in, '/', ALLOC_COMMAND);
	current_path = (char *)safe_malloc(sizeof(char) * (PATH_MAX + 1),
			ALLOC_COMMAND);
	*current_path = '\0';
	i = 0;
	while (in_cut[i])
	{
		if (check_dot(in_cut[i]))
			if (nbr_of_dot(in_cut[i]) == 2)
				remove_path(current_path);
			else if (!check_dot(in_cut[i]) || nbr_of_dot(in_cut[i]) == 1)
					add_path(current_path, in_cut[i]);
		i++;
	}
	res = get_res(current_path);
	return (res);
}
