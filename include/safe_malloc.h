/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 19:19:53 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/14 19:20:29 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAFE_MALLOC_H
# define SAFE_MALLOC_H

# include "imports.h"
# include <stdbool.h>
enum						e_action
{
	ALLOC_COMMAND,
	ALLOC_MINISHELL,
	DESTROY_COMMAND,
	NUKE,
};

typedef struct s_safe_malloc
{
	void					*ptr;
	bool					mark;
	struct s_safe_malloc	*next;
}							t_safe_malloc;

// sert a creer des mallocs dans une liste chaine
void						*safe_malloc(size_t size, enum e_action action);

// strdup but safe
char						*safe_strdup(char *s, enum e_action action);

char						*ft_itoa_safe(int n);

char						*ft_strjoin_safe(char const *s1, char const *s2,
								enum e_action action);

char						**ft_split_safe(char const *s, char c,
								enum e_action action);

#endif
