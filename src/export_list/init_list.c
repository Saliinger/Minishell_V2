/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 23:18:42 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/06 23:19:06 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>

char	*get_name_env(char *var)
{
	size_t		i;
	char	*name;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (var[i] == '=')
		i++;
	if (i == ft_strlen(var))
		return (ft_strdup(var));
	name = (char *)malloc(sizeof(char) * i + 1);
	if (!name)
		return (NULL);
	ft_strlcpy(name, var, i);
	return (name);
}

char	*get_value_env(char *var)
{
	size_t		i;
	size_t		len;
	char	*value;

	i = 0;
	len = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (var[i] == '=')
		i++;
	len = ft_strlen(var) - i;
	if (len == 0)
		return (NULL);
	value = (char *)malloc(sizeof(char) * len + 1);
	if (!value)
		return (NULL);
	ft_strlcpy(value, var + i, len + 1);
	return (value);
}


// add free list on return NULL
t_export_list	**init_export_list(char **env)
{
	size_t				i;
	t_export_list	**init;

	i = 0;
	init = (t_export_list **)malloc(sizeof(t_export_list));
	*init = NULL;
	while (env[i])
	{
		if (add_node_export(init, get_name_env(env[i]),
				get_value_env(env[i])) == 1)
			return (NULL);
		i++;
	}
	return (init);
}
