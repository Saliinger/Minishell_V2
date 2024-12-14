/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 19:22:46 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/14 19:22:48 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// expand if the first char is $ in case it's empty or else

char	*get_name(char *s)
{
	int		i;
	int		start;
	int		end;
	char	*name;

	i = 0;
	start = 0;
	end = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
		i++;
	start = i;
	while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
		i++;
	end = i - start + 1;
	name = (char *)safe_malloc(sizeof(char) * end + 1, ALLOC_COMMAND);
	ft_strlcpy(name, s + start, end);
	return (name);
}

char	*tiny_expand(char *s, t_minishell *minishell)
{
	char			*res;
	char			*name;
	t_export_list	*var;

	if (*s == '$')
	{
		if (ft_strcmp(s, "$") == 0)
			return (s);
		if (ft_strcmp(s, "$?") == 0)
			res = ft_itoa_safe(*minishell->exit_status);
		else
		{
			name = get_name(s);
			var = find_export_node(name + 1, minishell->export_list);
			if (!var || !var->value)
			{
				res = safe_strdup(s + ft_strlen(name), ALLOC_COMMAND);
				return (res);
			}
			res = safe_strdup(var->value, ALLOC_COMMAND);
			res = ft_strjoin_safe(res, s + ft_strlen(name), ALLOC_COMMAND);
		}
	}
	else
		return (s);
	return (res);
}
