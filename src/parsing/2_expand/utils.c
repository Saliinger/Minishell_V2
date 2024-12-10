/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 23:04:25 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/09 18:34:23 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*add_char(char *s, char c)
{
	char	*res;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s);
	res = (char *)malloc(sizeof(char) * (len + 2));
	if (!res)
		return (free(s), NULL);
	while (s[i])
	{
		res[i] = s[i];
		i++;
	}
	res[i] = c;
	res[i + 1] = '\0';
	free(s);
	return (res);
}

static int	get_var_name(char *arg)
{
	int	len;

	len = 0;
	if (arg[len] == '$')
		len++;
	if (arg[len] == '?')
		return (2);
	while (arg[len] && (ft_isalpha(arg[len]) || ft_isdigit(arg[len])
			|| arg[len] == '_'))
		len++;
	return (len);
}

char	*clean_name(char *var)
{
	int		len;
	char	*res;

	len = 0;
	len = get_var_name(var);
	res = (char *)malloc(sizeof(char) * len + 1);
	ft_strlcpy(res, var, len + 1);
	return (res);
}
