/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:54:16 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/17 13:59:08 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool	check_name(char *str)
{
	char	*name;
	int		j;

	j = 0;
	name = NULL;
	name = get_name_env(str);
	if (!ft_isalpha(name[j]) && name[j] != '_')
		return (printerr("bash: export: `%s': not a valid identifier\n", name),
			false);
	j++;
	while (name[j] && name[j] != '=')
	{
		if (!ft_isdigit(name[j]) && !ft_isalpha(name[j]) && name[j] != '_')
			return (printerr("bash: export: `%s': not a valid identifier\n",
					name), false);
		j++;
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
	int	i;

	i = 1;
	if (nbr_of_line(command->clean_arg) > 1)
	{
		i = 1;
		while (command->clean_arg[i])
		{
			if (check_name(command->clean_arg[i]))
			{
				export_handler(command->clean_arg[i],
					get_name_env(command->clean_arg[i]),
					get_value_env(command->clean_arg[i]), minishell);
			}
			i++;
		}
	}
	else
		print_export_list(minishell->export_list);
	return (0);
}
