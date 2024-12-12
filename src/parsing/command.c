/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:22:58 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/09 18:34:28 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*extract_command(char *line)
{
	char	*command;
	int		i;
	int		j;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
		i++;
	if (!line[i])
		return (NULL);
	j = 0;
	while (line[i + j] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		j++;
	command = (char *)safe_malloc(sizeof(char) * j + 1, ALLOC_COMMAND);
	ft_strlcpy(command, line + i, j + 1);
	return (command);
}

t_command	*command_init(char *in)
{
	char	*line;

	line = extract_command(in);
	if (!line)
		return (NULL);
	if (checker_command(line, ECHO))
		return (trim(in, safe_strdup(ECHO, ALLOC_COMMAND), true, ECHO_ID));
	else if (checker_command(line, CD))
		return (trim(in, safe_strdup(CD, ALLOC_COMMAND), true, CD_ID));
	else if (checker_command(line, PWD))
		return (trim(in, safe_strdup(PWD, ALLOC_COMMAND), true, PWD_ID));
	else if (checker_command(line, EXPORT))
		return (trim(in, safe_strdup(EXPORT, ALLOC_COMMAND), true, EXPORT_ID));
	else if (checker_command(line, UNSET))
		return ( trim(in, safe_strdup(UNSET, ALLOC_COMMAND), true, UNSET_ID));
	else if (checker_command(line, ENV))
		return (trim(in, safe_strdup(ENV, ALLOC_COMMAND), true, ENV_ID));
	else if (checker_command(line, EXIT))
		return ( trim(in, safe_strdup(EXIT, ALLOC_COMMAND), true, EXIT_ID));
	else
		return (trim(in, line, false, -1));
}
