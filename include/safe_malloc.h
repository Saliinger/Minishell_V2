//
// Created by Alexis Noukan on 12/12/2024.
//

#ifndef MINISHELL_V2_SAFE_MALLOC_H
#define MINISHELL_V2_SAFE_MALLOC_H

#include "imports.h"

enum e_action
{
    ALLOC_COMMAND,
    ALLOC_MINISHELL,
    DESTROY_COMMAND,
    NUKE,
};

typedef struct s_safe_malloc
{
    void                    *ptr;
    bool                    mark;
    struct s_safe_malloc    *next;
}                           t_safe_malloc;

// sert a creer des mallocs dans une liste chaine
void    *safe_malloc(size_t size, enum e_action action);

// strdup but safe
char *safe_strdup(char *s,  enum e_action action);

char	*ft_itoa_safe(int n);

char	*ft_strjoin_safe(char const *s1, char const *s2, enum e_action action);

#endif //MINISHELL_V2_SAFE_MALLOC_H
