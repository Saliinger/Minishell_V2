/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 23:02:11 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/10 12:52:19 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	check_nbr_var(char *line)
{
	int	i;
	int	status;
	int	nbr;

	i = 0;
	status = 0;
	nbr = 0;
	status = 0;
	while (line[i])
	{
		status = in_quote(status, line[i]);
		if (line[i] == '$' && status >= 0)
			nbr++;
		i++;
	}
	return (nbr);
}

char	*add_expand(char *s, char *to_add)
{
	char	*res;
	int		i;

	i = 0;
	res = safe_strdup("", ALLOC_COMMAND);
	while (s[i])
	{
		res = add_char(res, s[i]);
		i++;
	}
	i = 0;
	if (to_add)
	{
		while (to_add[i])
		{
			res = add_char(res, to_add[i]);
			i++;
		}
	}
	return (res);
}

char	*expand(t_minishell *minishell, char *name)
{
	char			*res;
	t_export_list	*data;
	int				*exit;

	if (name[0] == '$' && name[1] == '?' && name[2] == '\0')
	{
		exit = minishell->exit_status;
		res = ft_itoa(*exit);
	}
	else if (ft_strlen(name) == 1 && *name == '$')
		res = safe_strdup("$", ALLOC_COMMAND);
	else
	{
		data = find_export_node(name + 1, minishell->exportList);
		if (data)
			res = safe_strdup(data->value, ALLOC_COMMAND);
		else
			return (NULL);
	}
	return (res);
}

char	*new_line(t_minishell *minishell, char *line)
{
	int		i;
	int		status;
	char	*res;
	char	*name;
	char	*extend;

	i = 0;
	res = safe_strdup("", ALLOC_COMMAND);
	status = 0;
	while (line[i])
	{
		status = in_quote(status, line[i]);
		if (line[i] == '$' && status >= 0)
		{
			name = clean_name(line + i);
			i += ft_strlen(name);
			extend = expand(minishell, name);
			res = add_expand(res, extend);
		}
		else
		{
			res = add_char(res, line[i]);
			i++;
		}
	}
	return (res);
}

char	**expand_in(char **arg, t_minishell *minishell)
{
	int		i;
	char	**res;
	char	*to_add;

	i = 0;
	res = NULL;
	while (i < nbr_of_line(arg))
	{
		if (check_nbr_var(arg[i]) > 0)
		{
			to_add = new_line(minishell, arg[i]);
			res = add_line(res, to_add, ALLOC_COMMAND);
		}
		else
			res = add_line(res, arg[i], ALLOC_COMMAND);
		i++;
	}
	return (res);
}
