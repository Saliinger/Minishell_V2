/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 23:19:12 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/06 23:19:16 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	modify_value(t_export_list **lst, char *name, char *value)
{
	t_export_list	*tmp;

	tmp = find_export_node(name, lst);
	if (tmp)
	{
		if (tmp->value)
			free(tmp->value);
		tmp->value = ft_strdup(value);
	}
	else
		return (1);
	return (0);
}

int modify_value_env(t_minishell *minishell, char *name, char *value)
{
    int line = 0;
    char *var;

    line = get_env_var(minishell, name, ft_strlen(name));
    fprintf(stderr, "%d\n", line);
    if (line != -1)
    {
        var = ft_strjoin(name, "=");
        var = ft_strjoin_frees1(var, value);
        delete_var(minishell, line);
        create_var(minishell, var);
    }
    return (0);
}