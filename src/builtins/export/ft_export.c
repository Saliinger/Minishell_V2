/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:54:16 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/13 21:45:41 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool	check_name(char *name)
{
	int	i;

	i = 0;
	if (!ft_isalpha(name[i]) && name[i] != '_')
		return (false);
	i++;
	while (name[i])
	{
		if (!ft_isdigit(name[i]) && !ft_isalpha(name[i]) && name[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

int	var_exist(char *name, t_minishell *minishell)
{
	int				line;
	t_export_list	*tmp;

	line = get_env_var(minishell, name, ft_strlen(name));
	tmp = find_export_node(name, minishell->export_list);
	if (line == -1 && !tmp)
		return (0);
	else if (line == -1)
		return (1);
	return (2);
}

static void	manage_export(t_minishell *minishell, char *name, char *value,
		char *line)
{
	modify_value(minishell->export_list, name, value);
	delete_var(minishell, get_env_var(minishell, name, ft_strlen(name)));
	create_var(minishell, line);
}

static void	export_handler(char *line, char *name, char *value,
		t_minishell *minishell)
{
	int	status;

	status = var_exist(name, minishell);
	if (status == 0)
	{
		add_node_export(minishell->export_list, name, value);
		if (value)
			create_var(minishell, line);
	}
	else if (status == 1)
	{
		if (value)
		{
			modify_value(minishell->export_list, name, value);
			create_var(minishell, line);
		}
	}
	else
	{
		if (value)
			manage_export(minishell, name, value, line);
	}
	merge_sort(minishell->export_list);
}

int	ft_export(t_command *command, t_minishell *minishell)
{
	int		i;
	char	*name;
	char	*value;

	i = 1;
	if (nbr_of_line(command->clean_arg) > 1)
	{
		while (command->clean_arg[i])
		{
			name = get_name_env(command->clean_arg[i]);
			if (!check_name(name))
			{
				printerr("bash: export: `%s': not a valid identifier\n", name);
				return (minishell->exit_status[0] = 1, 1);
			}
			i++;
		}
		i = 1;
		while (command->clean_arg[i])
		{
			name = get_name_env(command->clean_arg[i]);
			value = get_value_env(command->clean_arg[i]);
			export_handler(command->clean_arg[i], name, value, minishell);
			i++;
		}
	}
	else
		print_export_list(minishell->export_list);
	return (0);
}
