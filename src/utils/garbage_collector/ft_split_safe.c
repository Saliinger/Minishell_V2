/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_safe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 13:41:49 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/14 13:41:49 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/safe_malloc.h"

static void	ft_split_write_word_safe(char *dest, const char *src, char c)
{
	size_t	i;

	i = 0;
	while ((src[i] == c || src[i] == '\0') == 0)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

static int	ft_split_write(char **dest, char const *s, char c, enum e_action action)
{
	size_t	i;
	size_t	j;
	size_t	word;

	word = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] == c || s[i] == '\0') == 1)
			i++;
		else
		{
			j = 0;
			while ((s[i + j] == c || s[i + j] == '\0') == 0)
				j++;
			dest[word] = (char *)safe_malloc(sizeof(char) * (j + 1), action);
			ft_split_write_word_safe(dest[word], (char *)(s + i), c);
			i += j;
			word++;
		}
	}
	dest[word] = NULL;
	return (0);
}

char	**ft_split_safe(char const *s, char c, enum e_action action)
{
	char	**dest;

	if (!s)
		return (NULL);
	dest = safe_malloc(sizeof(char *) * (ft_countword(s, c) + 1), action);
	if (!dest)
		return (NULL);
	ft_split_write(dest, s, c, action);
	return (dest);
}
